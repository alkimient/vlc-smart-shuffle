cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

# Force C11 standard for all compilers
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Platform-specific compiler flags
if(MSVC)
    # Explicitly force C11 and enable experimental atomic support for MSVC
    add_compile_options(/std:c11)
    add_compile_options(/experimental:c11atomics)
endif()

# Include Path Logic
if(NOT VLC_INCLUDE_DIR)
    if(WIN32)
        set(VLC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vlc_sdk/include")
    else()
        set(VLC_INCLUDE_DIR "/usr/include/vlc")
    endif()
endif()

if(NOT VLC_LIBRARIES)
    if(WIN32)
        set(VLC_LIBRARIES "libvlccore" "libvlc")
    else()
        set(VLC_LIBRARIES "vlccore" "vlc")
    endif()
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
