#
# OSVR SysInfo library
#

set(_osvrSysInfo_headers
	EnvironmentVariables.h
	MemoryInformation.h
	OperatingSystem.h
	OSVRHDKInformation.h
	Platform.h
	SerialPort.h
	USBInformation.h
	Utilities.h)

set(_osvrSysInfo_src
	EnvironmentVariables.cpp
	MemoryInformation.cpp
	OperatingSystem.cpp
	OSVRHDKInformation.cpp
	SerialPort.cpp
	USBInformation.cpp
	Utilities.cpp)

set(_osvrSysInfo_deps)

# Dynamic library
add_library(osvrSysInfo
	SHARED ${_osvrSysInfo_src} ${_osvrSysInfo_headers})
target_link_libraries(osvrSysInfo
	PRIVATE
	${_osvrSysInfo_deps}
	${LIBUSB1_LIBRARIES}
	osvr::osvrUSBSerial
	PUBLIC
	Boost::system)
target_include_directories(osvrSysInfo
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}
	${LIBUSB1_INCLUDE_DIRS})

# Static library
add_library(osvrSysInfo_static
	STATIC ${_osvrSysInfo_src} ${_osvrSysInfo_headers})
target_link_libraries(osvrSysInfo_static
	PRIVATE
	${_osvrSysInfo_deps}
	${LIBUSB1_LIBRARIES}
	osvr::osvrUSBSerial
	PUBLIC
	osvr::osvrUtil
	Boost::system)
target_include_directories(osvrSysInfo_static
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}
	${LIBUSB1_INCLUDE_DIRS})

set_property(TARGET osvrSysInfo
	PROPERTY POSITION_INDEPENDENT_CODE 1)

# Generate export header
include(GenerateExportHeader)
generate_export_header(osvrSysInfo
	BASE_NAME OSVR_SYSINFO
	EXPORT_FILE_NAME Export.h)
target_compile_definitions(osvrSysInfo_static
	PUBLIC OSVR_SYSINFO_STATIC_DEFINE)


add_library(osvr::osvrSysInfo ALIAS osvrSysInfo)
add_library(osvr::osvrSysInfo_static ALIAS osvrSysInfo_static)

