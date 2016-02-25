cmake_minimum_required(VERSION 2.8)
project(turingmachine)

#set(USE_CLANG TRUE)

set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set (PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set (PROJECT_BINARY_DIR ${PROJECT_DIR}/build)
set (PROJECT_LIB_DIR ${PROJECT_DIR}/lib)

include_directories (${PROJECT_INCLUDE_DIR})

if (USE_CLANG)
	set(CMAKE_C_COMPILER /usr/bin/clang)
	set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif (USE_CLANG)

set (CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

add_subdirectory(include/json_spirit)
add_subdirectory(src)

add_executable(turingmachine main.cpp)

target_link_libraries(
	turingmachine
	Machine
	json_spirit)
