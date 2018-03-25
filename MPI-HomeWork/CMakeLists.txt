cmake_minimum_required(VERSION 3.8)
project(MPI_HomeWork)

include_directories(/usr/local/mpich/include)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main_mpi.cpp)
add_executable(MPI_HomeWork ${SOURCE_FILES})