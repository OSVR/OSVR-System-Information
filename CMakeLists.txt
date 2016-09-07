#
# OSVR System Report tool
#
cmake_minimum_required(VERSION 3.1.0)
project(osvr_system_report)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Options
#
option(BUILD_APPS "Build applications that use osvrDisplay." ON)
option(BUILD_TESTS "Build test programs and unit tests." ON)

#
# Default installation directories
#

include(GNUInstallDirs)

#
# Dependencies
#

#
# Third-party libraries
#
add_subdirectory(vendor)

#
# OSVR SysInfo
#
add_subdirectory(osvr)

include(CTest)
enable_testing()

if(BUILD_TESTS)
#	add_subdirectory(test)
endif()

if(BUILD_APPS)
	add_subdirectory(apps)
endif()

