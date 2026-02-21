cmake_minimum_required(VERSION 3.10.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# copy samples
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/samples/)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/samples/ 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/samples/ FILES_MATCHING PATTERN "*.spk")

project(sputnik_test VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sputnik_test sputnik_test.cpp)
