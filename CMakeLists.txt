cmake_minimum_required(VERSION 3.22.1)

project(listdos)

set(CMAKE_C_STANDARD=11)
set(CMAKE_BUILD_TYPE "Debug")

add_library(list STATIC list/list.c)
add_subdirectory(data)

add_executable(listdos src/main.c src/cmd.c)
target_link_libraries(listdos list data)