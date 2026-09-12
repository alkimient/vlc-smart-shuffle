cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

if(MSVC)
    # C17 is more stable in MSVC 2022 than strict C11 for these headers
    add_compile_options(/std:c17)
    add_compile_options(/experimental:c11atomics)
else()
    set(CMAKE_C_STANDARD 11)
endif()

if(NOT VLC_INCLUDE_DIR)
    if(WIN32)
        set(VLC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vlc_sdk/include")
    else()
        set(VLC_INCLUDE_DIR "/usr/include/vlc")
    endif()
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

if(NOT WIN32)
    target_compile_options(smart_shuffle PRIVATE -I/usr/include/vlc)
endif()

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle "vlccore" "vlc")
