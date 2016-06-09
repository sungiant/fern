cmake_minimum_required(VERSION 3.5)
project(fern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vm.cpp vm.h instr.h instr.cpp conf.h bm.h bm.cpp)
add_executable(fern ${SOURCE_FILES})