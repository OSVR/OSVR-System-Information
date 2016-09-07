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
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <cstdint>

namespace osvr {
namespace sysinfo {

/**
 * @brief Returns the total amount of memory available to the operating system
 * in megabytes.
 */
OSVR_SYSINFO_EXPORT uint64_t getTotalMemory();

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_MemoryInformation_h_GUID_5F47375A_FE5C_46C3_934A_F8C46A7F36CC

