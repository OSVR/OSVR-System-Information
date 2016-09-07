#
# osvr_system_report application
#

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

