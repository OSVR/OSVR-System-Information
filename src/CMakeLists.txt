

add_executable(osvr_system_report
	osvr_system_report.cpp
	EnvironmentVariables.h)

target_link_libraries(osvr_system_report
	jsoncpp_lib_static)

target_include_directories(osvr_system_report
	SYSTEM PRIVATE
	${CMAKE_SOURCE_DIR}/vendor/jsoncpp/include)

