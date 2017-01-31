#
# Unit tests and test programs
#

include(CMakeParseArguments REQUIRED)

function(add_osvr_test testname)
	set(options "") # no options
	set(singleValueArgs "") # no single-value arguments
	set(multiValueArgs LIBS SOURCES INCLUDE_DIRS SYSTEM_INCLUDE_DIRS) # lists of additional libraries and source files
	cmake_parse_arguments(add_osvr_test "${options}" "${singleValueArgs}" "${multiValueArgs}" ${ARGN})

	add_executable(${testname} ${testname}.cpp ${add_osvr_test_SOURCES})
	target_link_libraries(${testname} PRIVATE ${add_osvr_test_LIBS})
	target_include_directories(${testname} PRIVATE ${add_osvr_test_INCLUDE_DIRS})
	target_include_directories(${testname} SYSTEM PRIVATE ${add_osvr_test_SYSTEM_INCLUDE_DIRS})
	set_property(TARGET ${testname} PROPERTY CXX_STANDARD 11)
	target_compile_features(${testname} PRIVATE cxx_override)
	install(TARGETS ${testname}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime)
	add_test(NAME test_${testname} COMMAND ${testname})
endfunction()

add_osvr_test(test_OSVRHDKInformation
	SOURCES
	"${CMAKE_SOURCE_DIR}/osvr/SysInfo/OSVRHDKInformation.cpp"
	INCLUDE_DIRS
	"${CMAKE_SOURCE_DIR}"
	"${CMAKE_BINARY_DIR}"
	LIBS
	osvrSysInfo_static
)

