/** @file
    @brief Implementation

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

// Internal Includes
#include <osvr/SysInfo/OSVRHDKInformation.h>
#include <osvr/SysInfo/SerialPort.h>

// Library/third-party includes
#include <osvr/USBSerial/USBSerialEnum.h>
#include <boost/optional.hpp>

// Standard includes
#include <string>
#include <sstream>

// TODO get device manager notes about OSVR devices (Windows only)
// TODO get HDK hardware and firmware versions
// TODO get IR camera firmware veresion

namespace osvr {
namespace sysinfo {

namespace detail {

std::vector<std::string> retrieveHDKFirmwareVersion()
{
    std::vector<std::string> hdk_info;

    const static uint16_t OSVR_HDK_VID = 0x1532;
    const static uint16_t OSVR_HDK_PID = 0x0b00;

    for (auto &&usb_device : osvr::usbserial::enumerate(OSVR_HDK_VID, OSVR_HDK_PID)) {
        // Example input:
        //
        // Version 1.96  Aug 12 2016
        // Tracker:1.8.3.402
        //
        // Version 1.99 (RELEASE)  Nov 28 2016
        // Tracker:1.10.0.453

        SerialPort serial_port { usb_device.getPlatformSpecificPath(), 9600 };
        serial_port.writeLine("#?v");
        auto echoed_input = serial_port.readStringUntil();
        auto version_date_str = serial_port.readStringUntil();
        auto tracker_str = serial_port.readStringUntil();

        hdk_info.push_back(version_date_str);
        hdk_info.push_back(tracker_str);
        break;
    }

    return hdk_info;
}

boost::optional<HDKFirmwareInfo> parseHDKFirmwareInfo(const std::vector<std::string>& hdk_info)
{

    if (hdk_info.size() != 2)
        return boost::none;

    // Example input:
    //
    // Version 1.96  Aug 12 2016
    // Tracker:1.8.3.402
    //
    // Version 1.99 (RELEASE)  Nov 28 2016
    // Tracker:1.10.0.453

    HDKFirmwareInfo info;
    std::string release_type = "RELEASE";
    std::string junk; // to store garbage we don't care about
    std::string month, day, year;

    std::stringstream ss;
    ss << hdk_info.at(0);
    ss >> junk; // "Version"
    ss >> info.firmwareVersion;
    if (hdk_info.at(0).find("(") != std::string::npos) {
        ss >> release_type;
        release_type = release_type.substr(1, release_type.size() - 2);
    }
    info.releaseType = release_type;
    ss >> month >> day >> year;
    info.date = month + " " + day + " " + year;
    info.trackerVersion = hdk_info.at(1).substr(hdk_info.at(1).find(":") + 1);

    return info;
}

} // namespace detail

boost::optional<HDKFirmwareInfo> getHDKFirmwareInfo()
{
    const auto hdk_info = detail::retrieveHDKFirmwareVersion();
    return detail::parseHDKFirmwareInfo(hdk_info);
}

} // namespace sysinfo
} // namespace osvr

