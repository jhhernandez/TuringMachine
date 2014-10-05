cmake_minimum_required(VERSION 3.0)
project(turingmachine)

set(USE_CLANG TRUE)

if (USE_CLANG)
	set(CMAKE_C_COMPILER /usr/bin/clang)
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif (USE_CLANG)

set (CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

find_library(JSON_SPIRIT_STATIC_LIB NAMES libjson_spirit.a)

add_subdirectory(src)

add_executable(turingmachine main.cpp)

target_link_libraries(
	turingmachine
	Machine)

install(TARGETS turingmachine RUNTIME DESTINATION bin)