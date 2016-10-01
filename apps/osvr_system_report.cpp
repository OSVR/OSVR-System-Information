/** @file
    @brief Utility to generate system report.

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
#include <osvr/SysInfo/MemoryInformation.h>
#include <osvr/SysInfo/OperatingSystem.h>
#include <osvr/SysInfo/USBInformation.h>
#include <osvr/SysInfo/OSVRHDKInformation.h>

// Library/third-party includes
#include <json/value.h>
#include <json/writer.h>

// Standard includes
#include <ctime>
#include <iostream>

inline void usage()
{
    using std::cout;
    using std::endl;
    using std::flush;

    cout << "Usage: osvr_system_report [options]\n";
    cout << "\n";
    cout << "Options:\n";
    cout << "    -j         format report in JSON\n";
    cout << "    -t         format report in plain text\n";
    cout << "    -o FILE    write the output to FILE\n";
    cout << "    -h|--help  display this help\n";
    cout << "\n";
}

int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    using std::flush;
    using namespace osvr::sysinfo;

    // TODO handle command-line args

    Json::Value report;

    // TODO write function to nicely wrap console messages to fit detected terminal width
    std::cout << "Please attach this log, along with other information as directed about your problem, to an email to the support helpdesk at support@osvr.org." << std::endl;
    std::cout << std::endl;
    std::cout << "If you remove any portions due to privacy concerns, please clearly note this both in the edited log file as well as the body of the support email." << std::endl;
    std::cout << std::endl;

    std::time_t now = std::time(nullptr);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%FT%TZ", std::localtime(&now))) {
        report["timestamp"] = mbstr;
    }

    std::cout << "Collecting operating system information..." << std::flush;
    const auto os_name = getOSName();
    const auto os_version = getOSVersion();
    report["operatingSystem"]["name"] = os_name;
    report["operatingSystem"]["release"] = os_version;
    std::cout << "done!" << std::endl;
    std::cout << " -- Operating system: " << os_name << std::endl;
    std::cout << " -- Version: " << os_version << std::endl;

    std::cout << "Collecting system information..." << std::flush;
    const auto total_mem = getTotalMemory();
    report["systemInformation"]["totalMemory"] = total_mem;
    std::cout << "done!" << std::endl;
    std::cout << " -- Total memory: " << total_mem << " MB" << std::endl;

    std::cout << "Collecting environment variables..." << std::flush;
    const auto env_vars = getEnvironmentVariables();
    for (const auto& env_var : env_vars) {
        report["environmentVariables"][env_var.first] = env_var.second;
    }
    std::cout << "done!" << std::endl;
    std::cout << " -- Found " << env_vars.size() << " environment variables." << std::endl;

    std::cout << "Enumerating USB devices..." << std::flush;
    const auto usb_devices = getUSBDevices();
    Json::Value::UInt index = 0;
    for (const auto& usb_device : usb_devices) {
        report["usbDevices"][index]["vendor"] = usb_device.vendorId;
        report["usbDevices"][index]["product"] = usb_device.productId;
        report["usbDevices"][index]["busNumber"] = usb_device.busNumber;
        report["usbDevices"][index]["address"] = usb_device.address;
        report["usbDevices"][index]["path"] = usb_device.getPathString();
        report["usbDevices"][index]["manufacturerName"] = usb_device.manufacturerName;
        report["usbDevices"][index]["productName"] = usb_device.productName;
        report["usbDevices"][index]["serialNumber"] = usb_device.serialNumber;
        ++index;
    }
    std::cout << "done!" << std::endl;
    std::cout << " -- Found " << usb_devices.size() << " USB devices." << std::endl;

    std::cout << "Getting OSVR HDK firmware version information..." << std::flush;
    const auto firmware_info = getHDKFirmwareInfo();
    if (firmware_info) {
        std::cout << "done!" << std::endl;
        std::cout << " -- Firmware version: " << firmware_info->firmwareVersion << "." << std::endl;
        report["hdk"]["firmwareVersion"] = firmware_info->firmwareVersion;
        report["hdk"]["date"] = firmware_info->date;
        report["hdk"]["trackerVersion"] = firmware_info->trackerVersion;
        report["hdk"]["detailedInformation"] = firmware_info->detailedInformation;
    } else {
        std::cout << "no HDK detected." << std::endl;
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

    std::cout << report;

    return 0;
}

