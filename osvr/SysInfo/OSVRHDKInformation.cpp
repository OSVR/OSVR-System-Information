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
// - none

// Library/third-party includes
#include <osvr/USBSerial/USBSerialDevInfo.h>
#include <boost/asio/serial_port.hpp>

// Standard includes
// - none

namespace osvr {
namespace sysinfo {

// TODO get device manager notes about OSVR devices (Windows only)
// TODO get HDK hardware and firmware versions
// TODO get IR camera firmware veresion

HDKFirmwareInfo getHDKFirmwareInfo()
{
    HDKFirmwareInfo info;

    const static uint8_t OSVR_HDK_VID = 0x1532;
    const static uint8_t OSVR_HDK_PID = 0x0b00;

    auto usb_devices = getSerialDeviceList(OSVR_HDK_VID, OSVR_HDK_PID);
    if (usb_devices.empty())
        return info;

    
}

} // namespace sysinfo
} // namespace osvr

