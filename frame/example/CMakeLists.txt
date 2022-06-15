cmake_minimum_required(VERSION 3.5)

project(frame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(
    frame_exam
    frame_exam.cpp
)
target_link_libraries(
    frame_exam
    frame
)

add_library(
    module_jane
    SHARED
    module_jane.cpp
)

add_library(
    module_bob
    SHARED
    module_bob.cpp
)

add_executable(libelf++_exam libelf++_exam.cpp)
target_link_libraries(libelf++_exam ${LIBELFIN_LIBS})

add_executable(libdwarf++_exam libdwarf++_exam.cpp)
target_link_libraries(libdwarf++_exam ${LIBELFIN_LIBS})
