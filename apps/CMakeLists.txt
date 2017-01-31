#
# osvr_system_report application
#

find_package(jsoncpp REQUIRED)

add_executable(osvr_system_report
	osvr_system_report.cpp)

target_link_libraries(osvr_system_report
	jsoncpp_lib_static
	osvr::osvrSysInfo_static)

target_include_directories(osvr_system_report
	SYSTEM PRIVATE
	${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include)

# Run osvr_system_report when we execute tests
add_test(NAME osvr_system_report_test
	COMMAND osvr_system_report)

#
# osvr_doctor application
#

add_executable(osvr_doctor
	osvr_doctor.cpp)

target_link_libraries(osvr_doctor
	osvr::osvrSysInfo_static)

#target_include_directories(osvr_doctor
#	SYSTEM PRIVATE)

# Run osvr_doctor when we execute tests
add_test(NAME osvr_doctor_test
	COMMAND osvr_doctor)

#
# osvr_hdk application
#

add_executable(osvr_hdk
	osvr_hdk.cpp)

target_link_libraries(osvr_hdk
	osvr::osvrSysInfo_static
	osvr::osvrUSBSerial
	Boost::program_options)

#target_include_directories(osvr_hdk
#	SYSTEM PRIVATE)

# Run osvr_hdk when we execute tests
add_test(NAME osvr_hdk_test
	COMMAND osvr_hdk)

