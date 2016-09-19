#
# OSVR System Report tool
#
cmake_minimum_required(VERSION 3.1.0)
project(osvr_system_report)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(UseBackportedModules)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Options
#
option(BUILD_APPS "Build applications that use osvrDisplay." ON)
option(BUILD_TESTS "Build test programs and unit tests." ON)
option(BUILD_HEADER_DEPENDENCY_TESTS "Should we add targets to ensure that every public header compiles cleanly on its own? Increases number of targets greatly..." ON)

#
# Default installation directories
#

include(GNUInstallDirs)

#
# Dependencies
#

find_package(Libusb1 REQUIRED)

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
	set(HEADER_BASE ${CMAKE_SOURCE_DIR}/osvr)
	add_subdirectory(test)
endif()

if(BUILD_APPS)
	add_subdirectory(apps)
endif()

