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
option(OSVR_SYSINFO_BUILD_APPS "Build applications that use osvrDisplay." ON)
option(OSVR_SYSINFO_BUILD_TESTS "Build test programs and unit tests." ON)
option(OSVR_SYSINFO_BUILD_HEADER_DEPENDENCY_TESTS "Should we add targets to ensure that every public header compiles cleanly on its own? Increases number of targets greatly..." ON)

#
# Default installation directories
#

include(GNUInstallDirs)

#
# Dependencies
#

find_package(Libusb1 REQUIRED)
set(Boost_USE_STATIC_LIBS 1)
find_package(Boost REQUIRED COMPONENTS system program_options date_time regex)
find_package(osvr REQUIRED)

#
# Third-party libraries
#
add_subdirectory(vendor)

#
# OSVR SysInfo
#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory(osvr)

include(CTest)
enable_testing()

if(OSVR_SYSINFO_BUILD_TESTS)
	set(HEADER_BASE ${CMAKE_CURRENT_SOURCE_DIR}/osvr)
	add_subdirectory(test)
endif()

if(OSVR_SYSINFO_BUILD_APPS)
	add_subdirectory(apps)
endif()

