get_filename_component(_FILENAME ${CMAKE_CURRENT_LIST_FILE} NAME)
string(REGEX REPLACE "Find(.*)\.cmake$" "\\1" _LIBRARY_NAME "${_FILENAME}" )

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../../${_LIBRARY_NAME}" "${CMAKE_CURRENT_LIST_DIR}/../../${_LIBRARY_NAME}/lib")

#add_library(${_LIBRARY_NAME} STATIC IMPORTED)
#find_library(${_LIBRARY_NAME}_LIBRARY_PATH ${_LIBRARY_NAME} HINTS "${CMAKE_CURRENT_LIST_DIR}/../../${_LIBRARY_NAME}/lib")
#set_target_properties(${_LIBRARY_NAME} PROPERTIES IMPORTED_LOCATION ${${_LIBRARY_NAME}_LIBRARY_PATH})

target_include_directories(${_LIBRARY_NAME} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../../${_LIBRARY_NAME}/include")
target_include_directories(${_LIBRARY_NAME} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../../wrycore/include")

