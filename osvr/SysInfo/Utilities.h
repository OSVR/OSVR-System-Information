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

#ifndef INCLUDED_Utilities_h_GUID_B7AFDBC8_F46B_4324_9F14_9D61E715A53A
#define INCLUDED_Utilities_h_GUID_B7AFDBC8_F46B_4324_9F14_9D61E715A53A

// Internal Includes
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
// - none

// Standard includes
#include <string>   // string, wstring

namespace osvr {
namespace sysinfo {

OSVR_SYSINFO_EXPORT std::string to_string(const std::wstring& s);

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_Utilities_h_GUID_B7AFDBC8_F46B_4324_9F14_9D61E715A53A

