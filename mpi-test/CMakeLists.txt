cmake_minimum_required(VERSION 3.8)
project(mpi_test)

include_directories(/usr/local/mpich/include)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(mpi_test ${SOURCE_FILES})