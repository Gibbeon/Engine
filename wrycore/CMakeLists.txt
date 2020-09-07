cmake_minimum_required(VERSION 3.17)

include(cmake/global.cmake)
include(cmake/vcpkg.cmake)

project(core VERSION 1.0.0)

message(${CMAKE_TOOLCHAIN_FILE})

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)


# Project files and linking
add_library( ${PROJECT_NAME} STATIC ${source_list})

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
                           
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)    

find_package(gsl-lite CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE gsl::gsl-lite gsl::gsl-lite-v0 gsl::gsl-lite-v1)

if (MSVC)
# For MSVC, CMake sets certain flags to defaults we want to override.
# This replacement code is taken from sample in the CMake Wiki at
# https://gitlab.kitware.com/cmake/community/wikis/FAQ#dynamic-replace.
  foreach (flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if (NOT BUILD_SHARED_LIBS)
      string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
    endif()

    # Prevent D9025 warning for targets that have exception handling
    # turned off (/EHs-c- flag). Where required, exceptions are explicitly
    # re-enabled using the cxx_exception_flags variable.
    #string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
  endforeach()
endif()       
