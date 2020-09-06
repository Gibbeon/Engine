cmake_minimum_required(VERSION 3.17)
project(editor VERSION 1.0.0)

include(cmake/global.cmake)

execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Using File GLOB_RECURSE for source list!"
)

# Project files and linking
add_executable( ${PROJECT_NAME} ${source_list})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                        
