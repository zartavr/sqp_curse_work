cmake_minimum_required(VERSION 2.8)

project(listdos)

set(CMAKE_C_STANDARD=11)
set(CMAKE_C_FLAGS "-Werror")
set(CMAKE_BUILD_TYPE "Debug")


add_library(list STATIC list/list.c)
add_subdirectory(data)

add_executable(listdos main.c cmd.c)
target_link_libraries(listdos list data)