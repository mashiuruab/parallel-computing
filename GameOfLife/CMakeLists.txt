cmake_minimum_required(VERSION 3.8)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main_omp_nano.cpp)
add_executable(GameOfLife ${SOURCE_FILES})