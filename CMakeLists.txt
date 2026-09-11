cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

# We use manual paths because VLC does not provide a standard CMake config file
if(NOT VLC_INCLUDE_DIR)
    set(VLC_INCLUDE_DIR "include")
endif()

if(NOT VLC_LIBRARIES)
    set(VLC_LIBRARIES "libvlccore" "libvlc")
endif()

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
