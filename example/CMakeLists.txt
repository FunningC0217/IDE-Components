project(example)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../cmake)

find_package(CodeEditor REQUIRED)
find_package(Frame REQUIRED)

add_executable(codeeditor_exam
    codeeditor.cpp
)

target_link_libraries(
    codeeditor_exam
    Qt5::Core
    Qt5::Widgets
    IDE-COM::CodeEditor
)

add_executable(frame_exam

)
