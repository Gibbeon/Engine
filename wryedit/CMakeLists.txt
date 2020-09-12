cmake_minimum_required(VERSION 3.17)

include(../shared/cmake/global.cmake)

project(wryedit VERSION 1.0.0)

execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Using File GLOB_RECURSE for source list!"
)

# Project files and linking
add_executable( ${PROJECT_NAME} ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                        
#find_package(wrycore REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE wrycore)

#find_package(wrywin32 REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE wrywin32)

find_package(wryd3d12 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE wryd3d12)

include(../shared/cmake/common_projects.cmake)
