cmake_minimum_required(VERSION 3.17)
project(engine VERSION 1.0.0)

include(cmake/global.cmake)

# Project files and linking
add_executable(${PROJECT_NAME} ${source_list})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                        
