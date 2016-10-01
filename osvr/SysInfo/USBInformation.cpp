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
#include <osvr/SysInfo/USBInformation.h>

// Library/third-party includes
#include <libusb.h>

// Standard includes
#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace osvr {
namespace sysinfo {

USBDevice::USBDevice(libusb_device* device)
{
    struct libusb_device_descriptor desc;
    const auto ret = libusb_get_device_descriptor(device, &desc);
    if (ret < 0) {
        return;
    }

    vendorId = desc.idVendor;
    productId = desc.idProduct;
    busNumber = libusb_get_bus_number(device);
    address = libusb_get_device_address(device);

    uint8_t p[16];
    const auto cnt = libusb_get_port_numbers(device, p, sizeof(p));
    for (std::vector<uint8_t>::size_type i = 0; i < cnt; ++i) {
        path.push_back(p[i]);
    }

    libusb_device_handle* handle = nullptr;
    const auto ret_open = libusb_open(device, &handle);
    if (ret_open == LIBUSB_ERROR_NO_MEM) {
       throw std::runtime_error("Error allocating memory for libusb_open().");
    } else if (ret_open == LIBUSB_ERROR_ACCESS) {
       throw std::runtime_error("Insufficient permissions to open USB device. Try running as administrator or root.");
    } else if (ret_open == LIBUSB_ERROR_NO_DEVICE) {
       throw std::runtime_error("The device has been disconnected.");
    } else if (ret_open != 0) {
       throw std::runtime_error("Error opening USB device: " + std::to_string(ret_open));
    }

    char str[128];
    if (libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, (unsigned char*)str, 128) >= 0) {
        manufacturerName = std::string(str);
    }

    if (libusb_get_string_descriptor_ascii(handle, desc.iProduct, (unsigned char*)str, 128) >= 0) {
        productName = std::string(str);
    }

    if (libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, (unsigned char*)str, 128) >= 0) {
        serialNumber = std::string(str);
    }

    libusb_close(handle);
}

std::string USBDevice::getPathString() const
{
    std::ostringstream oss;
    bool first = true;
    for (const auto& p : path) {
        if (!first)
            oss << ".";
        oss << static_cast<unsigned int>(p);
        first = false;
    }
    return oss.str();
}


std::vector<USBDevice> getUSBDevices()
{
    const auto ret = libusb_init(nullptr);
    if (ret < 0)
        return {};

    // Enable debug ouput
    //libusb_set_debug(nullptr, LIBUSB_LOG_LEVEL_DEBUG);

    libusb_device** devs;
    const auto cnt = libusb_get_device_list(nullptr, &devs);
    if (cnt < 0)
        return {};

    std::vector<USBDevice> usb_devices;
    int i = 0;
    libusb_device* dev = nullptr;
    while ((dev = devs[i++]) != nullptr) {
        try {
            auto usb_device = USBDevice(dev);
            usb_devices.push_back(usb_device);
        } catch (const std::exception& e) {
            //std::cerr << "\nError reading USB device: " << e.what() << std::endl;
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(nullptr);

    return usb_devices;
}

} // namespace sysinfo
} // namespace osvr

