cmake_minimum_required(VERSION 3.17)

include(../shared/cmake/global.cmake)

project(wryd3d12 VERSION 1.0.0)

message(${CMAKE_TOOLCHAIN_FILE})

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)


# Project files and linking
add_library( ${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                           
#find_package(wrycore REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE wrycore)

find_package(wrywin32 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE wrywin32)

target_link_libraries(${PROJECT_NAME} PRIVATE d3d12.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE dxgi.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE d3dcompiler.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE dxguid.lib)

include(../shared/cmake/common_projects.cmake)