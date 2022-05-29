cmake_minimum_required(VERSION 3.5)

project(CodeEditor)

set(LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(include)

set(HPP
    include/private/textedit_p.hpp
    include/textedit.hpp
)

set(CPP
    src/private/textedit_p.cpp
    src/textedit.cpp
)

add_library(${PROJECT_NAME}
    SHARED ${HPP} ${CPP}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
    )
