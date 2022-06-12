cmake_minimum_required(VERSION 3.5)

project(codeeditor)

set(LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include(GNUInstallDirs)
include(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)
find_package(CodeEditor REQUIRED)

set(PRI_HPP
    src/private/textedit_p.hpp
    )

set(PRI_CPP
    src/private/textedit_p.cpp
    )

set(HPP
    src/textedit.hpp
)

set(CPP
    src/textedit.cpp
)

add_library(${PROJECT_NAME}
    SHARED
    ${PRI_HPP} ${PRI_CPP}
    ${HPP} ${CPP}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    )
