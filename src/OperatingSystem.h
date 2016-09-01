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

// Platform-specific includes
#if defined(OSVR_WINDOWS)
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
#else
#error "Unsupported platform."
#endif
    }

} // namespace sysinfo
} // namespace osvr


#endif // INCLUDED_OperatingSystem_h_GUID_24F0A89A_ECA2_4270_90B8_195965948F0C

