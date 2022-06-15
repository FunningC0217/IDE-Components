cmake_minimum_required(VERSION 3.0.2)

project(frame)
add_subdirectory(3rdparty)
include(3rdparty/libelfin.cmake)

add_subdirectory(src)
add_subdirectory(example)
