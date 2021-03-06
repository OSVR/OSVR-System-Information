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

#ifndef INCLUDED_OSVRHDKInformation_h_GUID_E5876805_90FF_4C47_9A9D_053E9870D32B
#define INCLUDED_OSVRHDKInformation_h_GUID_E5876805_90FF_4C47_9A9D_053E9870D32B

// Internal Includes
#include <osvr/SysInfo/Export.h>

// Library/third-party includes
#include <boost/optional.hpp>

// Standard includes
#include <string>
#include <vector>

namespace osvr {
namespace sysinfo {

// TODO get device manager notes about OSVR devices (Windows only)
// TODO get HDK hardware and firmware versions
// TODO get IR camera firmware veresion

struct HDKFirmwareInfo {
	std::string firmwareVersion;
	std::string releaseType;
	std::string date;
    std::string trackerVersion;
	std::string detailedInformation;
};

boost::optional<HDKFirmwareInfo> getHDKFirmwareInfo();

namespace detail {

std::vector<std::string> retrieveHDKFirmwareVersion();
boost::optional<HDKFirmwareInfo> parseHDKFirmwareInfo(const std::vector<std::string>& hdk_info);

} // namespace detail
} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_OSVRHDKInformation_h_GUID_E5876805_90FF_4C47_9A9D_053E9870D32B

