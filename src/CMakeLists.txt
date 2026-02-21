cmake_minimum_required(VERSION 3.10.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(sputnik_test VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sputnik_test sputnik_test.cpp)
