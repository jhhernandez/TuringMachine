cmake_minimum_required(VERSION 2.6)
project(turingmachine)

add_executable(turingmachine main.cpp)

install(TARGETS turingmachine RUNTIME DESTINATION bin)
