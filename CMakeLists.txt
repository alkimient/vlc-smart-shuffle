cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# VLC headers use GCC-style attributes. 
# If using MSVC (cl.exe), we need to be very careful with flags.
# If using clang-cl, it's much more compatible.
if(MSVC)
    add_compile_options(/experimental:c11atomics)
    # Bypass some of the strict syntax checks that trigger on VLC's GCC-style headers
    add_compile_options(/wd4267) # Ignore possible loss of data (size_t to int)
endif()

if(NOT VLC_INCLUDE_DIR)
    set(VLC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vlc_sdk/include")
endif()

if(NOT VLC_LIBRARIES)
    set(VLC_LIBRARIES "libvlccore" "libvlc")
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
