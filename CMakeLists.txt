cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_STANDARD=11)
set(CMAKE_C_FLAGS "-Werror")

project(listdos)

add_library(list STATIC list.c)

add_executable(listdos main.c)
target_link_libraries(listdos list)