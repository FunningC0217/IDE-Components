include_directories(
    ${CMAKE_SOURCE_DIR}/3rdparty/libelfin
    ${CMAKE_SOURCE_DIR}/3rdparty/libelfin/elf
    ${CMAKE_SOURCE_DIR}/3rdparty/libelfin/dwarf
)

set(LIBELFIN_LIBS dwarf++ elf++)
