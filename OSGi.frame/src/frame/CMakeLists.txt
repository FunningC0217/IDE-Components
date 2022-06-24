cmake_minimum_required(VERSION 3.5)

project(OSGi.frame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(HPP
    Container.hpp
    CmdParse.hpp
    Module.hpp
    Service.hpp
    Bundle.hpp
    LifeCycle.hpp
    )

set(CPP
    LifeCycle.cpp
    )

add_library(
    ${PROJECT_NAME}
    SHARED
    ${CPP}
    ${HPP}
    )

target_link_libraries(
    ${PROJECT_NAME}
    ${CLANG_LIBS}
    -lstdc++fs
    )

if(WIN32)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} -ldl)
else()
endif()
