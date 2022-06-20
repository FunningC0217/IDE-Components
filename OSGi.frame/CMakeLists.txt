cmake_minimum_required(VERSION 3.0.2)

project(OSGi.frame)
add_subdirectory(3rdparty)

# LIBELFIN_LIBS
include(3rdparty/libelfin.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake)

# CLANG_LIBS CLANG_VERSION CLANG_LIBDIR CLANG_CXXFLAGS
find_package(LibClang)

add_subdirectory(src)
add_subdirectory(example)
