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

#ifndef INCLUDED_GPUInformation_h_GUID_D3D4A2D4_40F5_4FAE_918D_0F6E0794B53F
#define INCLUDED_GPUInformation_h_GUID_D3D4A2D4_40F5_4FAE_918D_0F6E0794B53F

// Internal Includes
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <cstdint>
#include <string>
#include <vector>

namespace osvr {
namespace sysinfo {

struct GPUInfo {
    std::string vendor;
    std::string model;
    uint64_t memory;
};

inline std::vector<GPUInfo> getGPUInfo()
{
    std::vector<GPUInfo> gpu_info_list;
    // TODO
    return gpu_info_list;
}

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_GPUInformation_h_GUID_D3D4A2D4_40F5_4FAE_918D_0F6E0794B53F

