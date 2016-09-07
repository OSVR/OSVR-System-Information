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

#ifndef INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522
#define INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522

// Internal Includes
#include "Platform.h"

// Library/third-party includes
// - none

// Standard includes
#include <map>
#include <string>
#include <vector>
#include <iostream> // debugging

// Platform-specific includes
#if defined(OSVR_WINDOWS)
#include <windows.h>
#endif

#if defined(OSVR_POSIX)
#include <unistd.h>
extern char **environ;
#endif

namespace osvr {
namespace sysinfo {

using EnvironmentVariablesList = std::map<std::string, std::string>;

inline EnvironmentVariablesList getEnvironmentVariables()
{
    std::vector<std::string> strs;

#if defined(OSVR_WINDOWS)
    auto envvars = GetEnvironmentStrings();
    while (*envvars != '\0') {
        auto str = std::string(envvars);
        std::cerr << " -- Adding [" << str << "]..." << std::endl;
        strs.emplace_back(std::move(str));
        std::cerr << " -- Advancing envvars by " << strlen(envvars) << "." << std::endl;
        envvars += strlen(envvars);
        envvars++;
        std::cerr << " -- Top of loop char = " << (*envvars) << std::endl;
    }
    std::cerr << " -- Freeing environment variables." << std::endl;
    FreeEnvironmentStrings(envvars);
    std::cerr << " -- Freed environment variables." << std::endl;
#elif defined(OSVR_POSIX)
    auto envvars = environ;
    while (*envvars) {
        strs.emplace_back(std::string(*envvars));
        envvars++;
    }
#else
#error "Unsupported platform."
#endif

    std::cerr << " -- Instantiating env_vars..." << std::flush;
    EnvironmentVariablesList env_vars;
    std::cerr << "done!" << std::endl;

    std::cerr << " -- We have " << strs.size() << " environment variables to parse." << std::endl;
    for (auto str : strs) {
        std::cerr << " -- Splitting [" << str << "]..." << std::endl;

        if (str.empty())
            continue;

        // Ignore internal Windows environment variables
        if ('=' == str[0])
            continue;

        // Split VAR=VALUE strings into VAR and VALUE components
        auto pos = str.find('=');
        if (std::string::npos == pos)
            continue;

        auto var = str.substr(0, pos);
        auto value = std::string("");
        if (pos < str.size() - 1) {
            value = str.substr(pos + 1);
        }

        env_vars[var] = value;
    }

    return env_vars;
}

} // end namespace sysinfo
} // end namespace osvr

#endif // INCLUDED_EnvironmentVariables_h_GUID_BE501038_D072_4C13_8BD4_A06AB9243522

