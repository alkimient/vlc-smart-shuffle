cmake_minimum_required(VERSION 3.10)
project(vlc-smart-shuffle)

find_package(VLC REQUIRED)

add_library(smart_shuffle MODULE src/main.c)
set_target_properties(smart_shuffle PROPERTIES PREFIX "")

target_include_directories(smart_shuffle PRIVATE ${VLC_INCLUDE_DIR})
target_link_libraries(smart_shuffle ${VLC_LIBRARIES})
