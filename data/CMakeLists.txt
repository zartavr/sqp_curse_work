add_library(data STATIC ${CMAKE_CURRENT_SOURCE_DIR}/data.c
                        ${CMAKE_CURRENT_SOURCE_DIR}/player_interface.c 
                        ${CMAKE_CURRENT_SOURCE_DIR}/logmsg_interface.c)

target_include_directories(data PUBLIC ${PROJECT_SOURCE_DIR})