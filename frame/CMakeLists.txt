cmake_minimum_required(VERSION 3.5)

project(frame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(Qt5 COMPONENTS Core)

set(HPP
    src/module.hpp
    src/loader.hpp
    )

set(CPP
    src/loader.cpp
    )

add_library(${PROJECT_NAME}
    SHARED ${CPP} ${HPP}
)

target_link_libraries(
    ${PROJECT_NAME}
    Qt5::Core
    )

add_executable(frame_exam
    example/frame_exam.cpp
)
target_link_libraries(frame_exam
    ${PROJECT_NAME}
)

add_library(module_jane
    SHARED
    example/module_jane.cpp)

add_library(module_bob
    SHARED
    example/module_bob.cpp)

