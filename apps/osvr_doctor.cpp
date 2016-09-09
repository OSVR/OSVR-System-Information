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

int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    using std::flush;
    using namespace osvr::sysinfo;

    bool all_okay = true;

    const auto usb_devices = getUSBDevices();

    std::cout << "Searching for OSVR HDK..." << std::flush;
    bool found = false;
    for (const auto& usb_device : usb_devices) {
        if (usb_device.vendorId == 0x1532 && usb_device.productId == 0x0b00) {
            found = true;
            std::cout << "found!" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "not found." << std::endl;
        all_okay = false;
    }


    std::cout << "Searching for OSVR IR camera..." << std::flush;
    found = false;
    for (const auto& usb_device : usb_devices) {
        if (usb_device.vendorId == 0xbda && usb_device.productId == 0x57e8) {
            found = true;
            std::cout << "found!" << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "not found." << std::endl;
        all_okay = false;
    }




    // TODO Driver store: pnputil -e
    // TODO CDC driver: dir /s "%systemroot%\system32\DriverStore\FileRepository\osvr_cdc.inf*"
    // TODO DFU driver: dir /s "%systemroot%\system32\DriverStore\FileRepository\atmel_usb_dfu.inf*"

    // TODO SetupAPI - at least one will fail, that's OK:
    //   "%SystemRoot%\setupapi.log"
    //   "%SystemRoot%\inf\setupapi.app.log"
    //   "%SystemRoot%\inf\setupapi.dev.log"

    // TODO DPInst: "%SystemRoot%\dpinst.log"

    // TODO Get all USB devices: "Get-WmiObject -class Win32_PnPEntity -namespace 'root\CIMV2' | where {$_.DeviceID -like 'USB\*'} | select name,hardwareid,status,service,errordescription"
    // TODO  Get all HID devices - should get one like HID\VID_1532&PID_0B00&REV_0100&MI_02
    //   "Get-WmiObject -class Win32_PnPEntity -namespace 'root\CIMV2' | where {$_.DeviceID -like 'HID\*'} | select name,hardwareid,status,service,errordescription"
    // TODO Get all monitors - should see SEN1019 (old firmware) or SVR1019 (new firmware)
    //   "Get-WmiObject -class Win32_PnPEntity -namespace 'root\CIMV2' | where {$_.DeviceID -like 'MONITOR\*'} | select name,hardwareid,status,service,errordescription"

    // TODO get signed driver data
    //   "Get-WmiObject -class Win32_PnPSignedDriver -namespace 'root\CIMV2' | where {$_.HardwareID -like 'USB\VID_1532&PID_0B00*'} | Select -Property * -ExcludeProperty __*,SystemProperties"

    // TODO This doozy gets the data that shows up in "Events" in a device manager properties dialog.
    // HDK USB hardware ID 
    //   "Get-WinEvent -FilterHashtable @{ProviderName=@('Microsoft-Windows-UserPnp','Microsoft-Windows-Kernel-PnP')}  | where {$_.Message.Contains('VID_1532&PID_0B00')} | select TimeCreated,Message | Sort-Object TimeCreated |fl"
    // TODO Sensics unofficial and official monitor PNP hardware IDs
    //   "Get-WinEvent -FilterHashtable @{ProviderName=@('Microsoft-Windows-UserPnp','Microsoft-Windows-Kernel-PnP')}  | where {$_.Message.Contains('DISPLAY\SVR') -or $_.Message.Contains('DISPLAY\SEN')} | select TimeCreated,Message | Sort-Object TimeCreated |fl"

    // TODO direct mode info
    // Direct Mode Vendor:	NVIDIA
    // Direct Mode Version:	368.81

    // TODO get list of displays and related info
    // TODO get list of USB devices and related info (tree format)
    // TODO zip up all relevant log files
    // TODO zip up all relevant configuration files
    // TODO get list of installed OSVR software and versions
    // TODO get processor name and speed
    // TODO get total RAM
    // TODO get graphics card name and VRAM
    // TODO get OSVR HDK info:
    // TODO     - hardware version
    // TODO     - firmware version
    // TODO     - serial number
    // TODO     - IR camera firmware version
    // TODO get player info (gender, height, vision, etc.)
    // TODO get version of SteamVR
    // TODO get SteamVR paths (vrpathreg) and info
    // TODO get webvr and browser information (see email from Yuval)

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



