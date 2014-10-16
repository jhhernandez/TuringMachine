cmake_minimum_required(VERSION 3.0)
project(turingmachine)

set(USE_CLANG TRUE)

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

find_library(JSON_SPIRIT_SHARED_LIB NAMES libjson_spirit.so PATHS ${PROJECT_LIB_DIR})

add_subdirectory(src)

add_executable(turingmachine main.cpp)

target_link_libraries(
	turingmachine
	Machine)

#install(TARGETS turingmachine RUNTIME DESTINATION bin)