cmake_minimum_required(VERSION 3.17)

include(../shared/cmake/global.cmake)

project(wrycore VERSION 1.0.0)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)


# Project files and linking
add_library( ${PROJECT_NAME} STATIC ${SOURCE_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                           
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)    

find_package(gsl-lite CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC gsl::gsl-lite gsl::gsl-lite-v0 gsl::gsl-lite-v1)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json nlohmann_json::nlohmann_json)


include(../shared/cmake/common_projects.cmake)
