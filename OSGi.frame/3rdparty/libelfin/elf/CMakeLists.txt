project(elf++)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} elf_SRC)

add_library(
    ${PROJECT_NAME}
    SHARED
    ${elf_SRC}
)

