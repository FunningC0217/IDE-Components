cmake_minimum_required(VERSION 3.0.2)

project(archvice)

set(INC
    CppTarget.hpp
    CppParse.hpp
    Archive.cpp
)

set(SRC
    CppParse.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${INC}
    ${SRC}
)

target_link_libraries(
    ${PROJECT_NAME}
    ${CLANG_LIBS}
    pthread
)

