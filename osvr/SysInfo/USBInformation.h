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

#ifndef INCLUDED_USBInformation_h_GUID_47671E6E_F29F_4983_A6E9_16B25B894A88
#define INCLUDED_USBInformation_h_GUID_47671E6E_F29F_4983_A6E9_16B25B894A88

// Internal Includes
#include <osvr/SysInfo/Export.h>
#include <osvr/SysInfo/Platform.h>

// Library/third-party includes
#include <libusb.h>

// Standard includes
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace osvr {
namespace sysinfo {

class USBDevice {
public:
    USBDevice(libusb_device* device);
    std::string getPathString() const;

    uint16_t vendorId = 0x0000;
    uint16_t productId = 0x0000;
    uint8_t busNumber = 0x00;
    uint8_t address = 0x00;
    std::vector<uint8_t> path;

    std::string manufacturerName = "";
    std::string productName = "";
    std::string serialNumber = "";
};

OSVR_SYSINFO_EXPORT std::vector<USBDevice> getUSBDevices();

} // namespace sysinfo
} // namespace osvr

#endif // INCLUDED_USBInformation_h_GUID_47671E6E_F29F_4983_A6E9_16B25B894A88

