cmake_minimum_required(VERSION 3.0.2)

project(OSGi.frame)
set(OSGi.frame_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# CLANG_LIBS CLANG_VERSION CLANG_LIBDIR CLANG_CXXFLAGS
find_package(LibClang)
include(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libelfin.cmake)

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(example)

