/** @file
    @brief Test functions in OSVRHDKInformation.h

    @date 2017

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Copyright 2017 Sensics, Inc.
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
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "osvr/SysInfo/OSVRHDKInformation.h"

// Library/third-party includes
// - none

// Standard includes
// - none

void test_parseHDKFirmwareInfo(const std::vector<std::string>& input, const osvr::sysinfo::HDKFirmwareInfo& expected)
{
    const auto actual = osvr::sysinfo::detail::parseHDKFirmwareInfo(input);
    CHECK(actual);

    CHECK(actual->firmwareVersion == expected.firmwareVersion);
    CHECK(actual->releaseType == expected.releaseType);
    CHECK(actual->date == expected.date);
    CHECK(actual->trackerVersion == expected.trackerVersion);
    CHECK(actual->detailedInformation == expected.detailedInformation);
}

TEST_CASE("parse HDK firmware info", "[OSVRHDKInformation]")
{
    const std::vector<std::string> fw196 = {
        "Version 1.96  Aug 12 2016",
        "Tracker:1.8.3.402"
    };

    osvr::sysinfo::HDKFirmwareInfo fw196_expected;
    fw196_expected.firmwareVersion = "1.96";
    fw196_expected.releaseType = "RELEASE";
    fw196_expected.date = "Aug 12 2016";
    fw196_expected.trackerVersion = "1.8.3.402";
    fw196_expected.detailedInformation = "";

    test_parseHDKFirmwareInfo(fw196, fw196_expected);

    const std::vector<std::string> fw199 = {
        "Version 1.99 (RELEASE)  Nov 28 2016",
        "Tracker:1.10.0.453"
    };

    osvr::sysinfo::HDKFirmwareInfo fw199_expected;
    fw199_expected.firmwareVersion = "1.99";
    fw199_expected.releaseType = "RELEASE";
    fw199_expected.date = "Nov 28 2016";
    fw199_expected.trackerVersion = "1.10.0.453";
    fw199_expected.detailedInformation = "";

    test_parseHDKFirmwareInfo(fw199, fw199_expected);
}

