cmake_minimum_required(VERSION 3.5)

project(fileeditor)

set(LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(PRI_HPP
    src/private/textedit_p.hpp
    src/private/edit_p.hpp
)

set(HPP
    src/textdocument.h
    src/textedit.h
    src/edit.hpp
)

set(CPP
    src/textdocument.cpp
    src/textedit.cpp
    src/edit.cpp
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
