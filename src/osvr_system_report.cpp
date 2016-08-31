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

// Internal Includes
#include "EnvironmentVariables.h"

// Library/third-party includes
#include <json/value.h>
#include <json/writer.h>

// Standard includes
#include <iostream>

int main(int argc, char* argv[])
{
    // TODO handle command-line args

    Json::Value report;
    auto env_vars = osvr::sysinfo::getEnvironmentVariables();
    for (const auto& env_var : env_vars) {
        //std::cout << "[" << env_var.first << "] = [" << env_var.second << "]" << std::endl;
        report["environmentVariables"][env_var.first] = env_var.second;
    }

    std::cout << report;

    return 0;
}

