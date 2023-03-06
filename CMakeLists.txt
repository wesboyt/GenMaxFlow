cmake_minimum_required(VERSION 3.21)
project(GenMaxFlows)
set(SOURCE_FILES example.cpp)
set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 23)
add_executable(GenMaxFlows ${SOURCE_FILES})
target_link_libraries(GenMaxFlows)

