cmake_minimum_required(VERSION 3.0.2)

project(archvice)

add_executable(
    ${PROJECT_NAME}
    CmdParse.hpp
    CppParse.hpp
    CppParse.cpp
    Archive.cpp
    )
