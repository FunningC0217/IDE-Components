include(GNUInstallDirs)

set(LIBELFIN_LIBS dwarf++ elf++)

include_directories(
    ${OSGi.frame_ROOT}/3rdparty/libelfin
    ${OSGi.frame_ROOT}/3rdparty/libelfin/dwarf
    ${OSGi.frame_ROOT}/3rdparty/libelfin/elf
)
