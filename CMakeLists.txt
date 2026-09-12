cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

# Force C11 standard to support VLC headers (Atomics and _Generic)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT VLC_INCLUDE_DIR)
    set(VLC_INCLUDE_DIR "/usr/include/vlc")
endif()

if(NOT VLC_LIBRARIES)
    set(VLC_LIBRARIES "vlccore" "vlc")
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
