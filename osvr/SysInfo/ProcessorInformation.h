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

#ifndef INCLUDED_ProcessorInformation_h_GUID_5860F7FE_AA29_4629_92D6_629C8DDF9CF0
#define INCLUDED_ProcessorInformation_h_GUID_5860F7FE_AA29_4629_92D6_629C8DDF9CF0

// Internal Includes
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <iostream>

namespace osvr {
namespace sysinfo {

struct CPUInformation {
    // TODO
};

inline CPUInformation getCPUInformation()
{
    // TODO
}

inline std::ostream& operator<<(std::ostream& ostr, CPUInformation)
{
    // TODO
}

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_ProcessorInformation_h_GUID_5860F7FE_AA29_4629_92D6_629C8DDF9CF0

