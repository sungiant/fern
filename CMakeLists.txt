cmake_minimum_required(VERSION 3.5)
project(fern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

message(STATUS "start running cmake...")

find_package(Boost 1.60.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()


set(SOURCE_FILES main.cpp vm.cpp vm.h instr.h instr.cpp conf.h bm.h bm.cpp)
add_executable(fern ${SOURCE_FILES})

if(Boost_FOUND)
    target_link_libraries(fern ${Boost_LIBRARIES})
endif()
