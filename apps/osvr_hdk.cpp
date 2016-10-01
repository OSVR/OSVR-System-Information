/** @file
    @brief Utility program to configure OSVR HDK 1.x and 2.0.

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
#include <osvr/SysInfo/SerialPort.h>
#include <osvr/USBSerial/USBSerialEnum.h>

// Library/third-party includes
#include <boost/program_options.hpp>

// Standard includes
#include <iostream>
#include <memory>
#include <string>

static bool verbose = false;

class HDK {
public:
    HDK();

    void command(const std::string& cmd);
    std::string output();

private:
    std::unique_ptr<osvr::sysinfo::SerialPort> serialPort_;
};

HDK::HDK()
{
    static const uint16_t OSVR_HDK_VID = 0x1532;
    static const uint16_t OSVR_HDK_PID = 0x0b00;

    for (auto&& usb_device : osvr::usbserial::enumerate(OSVR_HDK_VID, OSVR_HDK_PID)) {
        std::unique_ptr<osvr::sysinfo::SerialPort> serial_port(new osvr::sysinfo::SerialPort(usb_device.getPlatformSpecificPath(), 115200));
        serialPort_ = std::move(serial_port);
        break;
    }

    if (!serialPort_) {
        throw std::runtime_error("Couldn't find OSVR HDK. Check the cables to make sure everything is plugged in.");
    }
}

void HDK::command(const std::string& cmd)
{
    serialPort_->writeLine("cmd");
    auto echoed_input = serialPort_->readStringUntil();
}

std::string HDK::output()
{
    auto output = serialPort_->readStringUntil(">");
    return output;
}

void reset_hdmi()
{
    auto hdk = HDK{};
    hdk.command("#hi");
    std::cout << hdk.output() << std::endl;
}

void hdmi_info()
{
    auto hdk = HDK{};
    hdk.command("#hr");
    std::cout << hdk.output() << std::endl;
}

void firmware_version()
{
    auto hdk = HDK{};
    hdk.command("#?v");
    std::cout << hdk.output() << std::endl;
    hdk.command("#?f");
    std::cout << hdk.output() << std::endl;
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("verbose", "verbose output")
        ("reset-hdmi", "Reset HDMI")
        ("hdmi-info", "Gets HDMI status")
        ("firmware-version", "Gets firmware version")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    if (vm.count("verbose")) {
        verbose = true;
    }

    try {
        if (vm.count("reset-hdmi")) {
            reset_hdmi();
        }

        if (vm.count("hdmi-info")) {
            hdmi_info();
        }

        if (vm.count("firmware-version")) {
            firmware_version();
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

