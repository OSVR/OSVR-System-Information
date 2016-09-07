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

#ifndef INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522
#define INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522

// Internal Includes
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <map>
#include <string>

namespace osvr {
namespace sysinfo {

using EnvironmentVariablesList = std::map<std::string, std::string>;

OSVR_SYSINFO_EXPORT EnvironmentVariablesList getEnvironmentVariables();

} // end namespace sysinfo
} // end namespace osvr

#endif // INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522

