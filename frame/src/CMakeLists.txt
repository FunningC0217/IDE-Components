cmake_minimum_required(VERSION 3.5)

project(frame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(HPP
    module.hpp
    loader.hpp
    )

set(CPP
    loader.cpp
    )

add_library(${PROJECT_NAME}
    SHARED ${CPP} ${HPP}
)

