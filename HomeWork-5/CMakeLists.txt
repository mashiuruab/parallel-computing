cmake_minimum_required(VERSION 3.8)
project(HomeWork_5)

include_directories(/usr/local/mpich/include)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES non_blocking/main_ns.cpp)
add_executable(HomeWork_5 ${SOURCE_FILES})