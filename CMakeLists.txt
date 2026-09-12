cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

# Use C11 standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

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
        set(VLC_LIBRARIES "vlccore" "vlc")
    else()
        set(VLC_LIBRARIES "vlccore" "vlc")
    endif()
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
