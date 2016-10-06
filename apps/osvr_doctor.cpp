/** @file
    @brief Tool for troubleshooting OSVR HDK.

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
#include <osvr/SysInfo/EnvironmentVariables.h>
#include <osvr/SysInfo/OperatingSystem.h>
#include <osvr/SysInfo/MemoryInformation.h>
#include <osvr/SysInfo/USBInformation.h>

// Library/third-party includes
// - none

// Standard includes
#include <iostream>

bool detect_usb_device(const std::vector<osvr::sysinfo::USBDevice>& usb_devices, const std::string& name, const int vendor_id, const int product_id)
{
    std::cout << "Searching for " << name << "..." << std::flush;
    bool found = false;
    for (const auto& usb_device : usb_devices) {
        if (usb_device.vendorId == vendor_id && usb_device.productId == product_id) {
            found = true;
            std::cout << "found!" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "not found." << std::endl;
    }

    return found;
}


bool detect_osvr_usb_devices()
{
    const auto usb_devices = osvr::sysinfo::getUSBDevices();

    bool all_okay = true;

    struct USBDeviceNeedle {
        std::string name;
        int vendor_id;
        int product_id;
    };

    std::vector<USBDeviceNeedle> usb_device_needles {
        { "OSVR belt box USB hub", 0x05e3, 0x0610 },
        { "OSVR belt box audio", 0x0572, 0x1806 },
        { "OSVR HDK USB hub", 0x0424, 0x2134 },
        { "OSVR HDK processor", 0x1532, 0x0b00 },
        { "OSVR IR tracking camera", 0x0bda, 0x57e8 }
    };

    for (const auto& needle : usb_device_needles) {
        if (!detect_usb_device(usb_devices, needle.name, needle.vendor_id, needle.product_id))
            all_okay = false;
    }

    return all_okay;
}

int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    using std::flush;
    using namespace osvr::sysinfo;

    bool all_okay = true;

    if (!detect_osvr_usb_devices())
        all_okay = false;



    if (all_okay) {
        std::cout << "\nWe didn't detect any problems.\n" << std::endl;
        std::cout << "If you're experiencing a problem, run\n"
            "osvr_system_report to generate a system report and\n"
            "email it along with a description of the problem\n"
            "to <support@osvr.org> for further assistance." << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cout << "\nWe found one or more problems above.\n" << std::endl;
        std::cout << "If you're experiencing a problem, run\n"
            "osvr_system_report to generate a system report and\n"
            "email it along with a description of the problem\n"
            "to <support@osvr.org> for further assistance." << std::endl;
        return EXIT_FAILURE;
    }
}

