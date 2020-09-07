cmake_minimum_required(VERSION 3.17)

include(cmake/global.cmake)
include(cmake/vcpkg.cmake)
#include(${CMAKE_TOOLCHAIN_FILE})

project(editor VERSION 1.0.0)

execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Using File GLOB_RECURSE for source list!"
)

# Project files and linking
add_executable( ${PROJECT_NAME} ${source_list})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                        
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

find_package(core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE core)


