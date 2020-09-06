execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --green --bold "Including vkpkg.cmake file"
)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)

  execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --green --bold "Including 123 vcpkg.cmake file"
  )

  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
  elseif(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  
    execute_process(COMMAND
      ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
      ${CMAKE_COMMAND} -E cmake_echo_color --red --bold "Environment VCPKG_ROOT not specified, did not include vcpkg"
  ) 
  else ()
    execute_process(COMMAND
    ${CMAKE_COMMAND} -E env CLICOLOR_FORCE=1
    ${CMAKE_COMMAND} -E cmake_echo_color --green --bold "CMAKE_TOOLCHAIN_FILE was specified on the command line or was set as a default"
  )
endif()
