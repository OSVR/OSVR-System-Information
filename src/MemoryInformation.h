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

#ifndef INCLUDED_MemoryInformation_h_GUID_5F47375A_FE5C_46C3_934A_F8C46A7F36CC
#define INCLUDED_MemoryInformation_h_GUID_5F47375A_FE5C_46C3_934A_F8C46A7F36CC

// Internal Includes
#include "Platform.h"

// Library/third-party includes
#if defined(OSVR_WINDOWS)
#include <windows.h>
#elif defined(OSVR_LINUX)
#include <sys/sysinfo.h>
#elif defined(OSVR_MACOSX)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif

// Standard includes
#include <cstdint>

namespace osvr {
namespace sysinfo {

/**
 * @brief Returns the total amount of memory available to the operating system
 * in megabytes.
 */
inline uint64_t getTotalMemory()
{
#if defined(OSVR_WINDOWS)
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    return static_cast<uint64_t>(statex.ullTotalPhys / 1024 / 1024);
#elif defined(OSVR_LINUX)
    struct sysinfo info;
    auto ret = sysinfo(&info);
    const auto mem_mb = (sysinfo.totalram * sysinfo.mem_unit) / 1024 / 1024;
    return static_cast<uint64_t>(mem_mb);
#elif defined(OSVR_MACOSX)
    int mib[] = { CTL_HW, HW_MEMSIZE };
    int64_t value = 0;
    size_t length = sizeof(value);
    if (0 == sysctl(mib, 2, &value, &length, NULL, 0)) {
        return static_cast<uint64_t>(value / 1024 / 1024);
    }
    return 0;
#else
#error "Unsupported platform."
#endif
}

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_MemoryInformation_h_GUID_5F47375A_FE5C_46C3_934A_F8C46A7F36CC

