/** @file
    @brief Header

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_OperatingSystem_h_GUID_24F0A89A_ECA2_4270_90B8_195965948F0C
#define INCLUDED_OperatingSystem_h_GUID_24F0A89A_ECA2_4270_90B8_195965948F0C

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
#include <string>
#include <sstream>

// Platform-specific includes
#if defined(OSVR_WINDOWS)
#include <windows.h>
typedef LONG(NTAPI* fnRtlGetVersion)(PRTL_OSVERSIONINFOW lpVersionInformation);
#elif defined(OSVR_POSIX)
#include <sys/utsname.h>
#endif


namespace osvr {
namespace sysinfo {

    /**
     * @brief Returns the name of the operating system.
     */
    std::string getOSName();

    /**
     * @brief Returns the version number of the operating system.
     */
    std::string getOSVersion();

    //
    // Implementations
    //

    inline std::string getOSName()
    {
        // TODO support OSVR_WINDOWS
#if defined(OSVR_POSIX)
        struct utsname info;
        const auto ret = uname(&info);
        if (0 != ret)
            return "";

        return info.sysname;
#elif defined(OSVR_WINDOWS)
        static auto RtlGetVersion = (fnRtlGetVersion)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlGetVersion");
        if (!RtlGetVersion)
            return "";

        RTL_OSVERSIONINFOEXW version_info = { 0 };
        version_info.dwOSVersionInfoSize = sizeof(version_info);
        const auto ret = RtlGetVersion((PRTL_OSVERSIONINFOW)&version_info);
        if (ret != 0)
            return "";

        const auto x = version_info.dwMajorVersion;
        const auto y = version_info.dwMinorVersion;
        const auto ws = (version_info.wProductType == VER_NT_WORKSTATION);
        const auto sm_serverr2 = (0 != GetSystemMetrics(SM_SERVERR2));
        const auto wh_server = version_info.wSuiteMask & VER_SUITE_WH_SERVER;
        const auto nt_workstation = (version_info.wProductType == VER_NT_WORKSTATION);

        SYSTEM_INFO system_info = {};
        GetSystemInfo(&system_info);
        const auto arch_x64 = (system_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64);

        if (x == 10 && y == 0) {
            return ws ? "Windows 10" : "Windows Server 2016";
        } else if (x == 6 && y == 3) {
            return ws ? "Windows 8.1" : "Windows Server 2012 R2";
        } else if (x == 6 && y == 2) {
            return ws ? "Windows 8" : "Windows erver 2012";
        } else if (x == 6 && y == 1) {
            return ws ? "Windows 7" : "Windows Server 2008 R2";
        } else if (x == 6 && y == 0) {
            return ws ? "Windows Vista" : "Windows Server 2008";
        } else if (x == 5 && y == 2) {
            if (wh_server) {
                return "Windows Home Server";
            } else if (nt_workstation && arch_x64) {
                return "Windows XP Professional x64 Edition";
            } else if (sm_serverr2) {
                return "Windows Server 2003 R2";
            } else /* !sm_server2 */ {
                return "Windows Server 2003";
            }
        } else if (x == 5 && y == 1) {
            return "Windows XP";
        } else if (x == 5 && y == 0) {
            return "Windows 2000";
        } else {
            return "Windows";
        }
#else
#error "Unsupported platform."
#endif
    }

    inline std::string getOSVersion()
    {
        // TODO support OSVR_WINDOWS
#if defined(OSVR_POSIX)
        struct utsname info;
        const auto ret = uname(&info);
        if (0 != ret)
            return "";

        return info.release;
#elif defined(OSVR_WINDOWS)
        static auto RtlGetVersion = (fnRtlGetVersion)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlGetVersion");
        if (!RtlGetVersion)
            return "";

        RTL_OSVERSIONINFOEXW version_info = { 0 };
        version_info.dwOSVersionInfoSize = sizeof(version_info);
        const auto ret = RtlGetVersion((PRTL_OSVERSIONINFOW)&version_info);
        if (ret != 0)
            return "";

        const auto major = version_info.dwMajorVersion;
        const auto minor = version_info.dwMinorVersion;
        const auto build = version_info.dwBuildNumber;
        const auto sp_str = version_info.szCSDVersion;

        std::ostringstream version;
        version << major << "." << minor << " (build " << build << ")";
        if (sp_str) {
            version << " " << sp_str;
        }
        return version.str();
#else
#error "Unsupported platform."
#endif
    }

} // namespace sysinfo
} // namespace osvr


#endif // INCLUDED_OperatingSystem_h_GUID_24F0A89A_ECA2_4270_90B8_195965948F0C

