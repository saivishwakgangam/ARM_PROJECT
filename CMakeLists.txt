cmake_minimum_required(VERSION 3.20)
project(ARM_PROJECT)
set(CMAKE_CXX_STANDARD 14)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/code/dataset.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(ARM_PROJECT
        code/fp_tree.cpp)
