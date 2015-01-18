cmake_minimum_required(VERSION 3.0.2)

include(ExternalProject)

function(write_config code)
  set(args ${ARGN} false)
  list(GET args 0 is_init)
  unset(args)
  
  if(is_init)
    set(mode WRITE)
  else()
    set(mode APPEND)
  endif()
  
  set(path ${PROJECT_BINARY_DIR}/cmake/vendor.cmake)
  string(CONFIGURE ${code} code @ONLY)
  file(${mode} ${path} ${code})
endfunction()

write_config([[
  set(vendor_include_dirs
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
  )
  unset(vendor_libraries)
]] true)

if(NOT BUILD_DEPENDENCY AND NOT BUILD_LIBRARY)
  return()
endif()

# Google Mock
ExternalProject_Add(google_mock
  SVN_REPOSITORY http://googlemock.googlecode.com/svn/tags/release-1.7.0
  CMAKE_ARGS -DBUILD_SHARED_LIBS=${BUILD_SHAERD}
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
)
ExternalProject_Get_Property(google_mock BINARY_DIR)
ExternalProject_Get_Property(google_mock SOURCE_DIR)

write_config([[
  list(APPEND vendor_include_dirs
    $<BUILD_INTERFACE:@SOURCE_DIR@/include>
    $<BUILD_INTERFACE:@SOURCE_DIR@/gtest/include>
  )
  link_directories(
    @BINARY_DIR@
    @BINARY_DIR@/gtest
  )
  list(APPEND vendor_libraries
    gmock
    gtest
  )
  
  install(DIRECTORY @SOURCE_DIR@/include DESTINATION .)
  install(DIRECTORY @SOURCE_DIR@/gtest/include DESTINATION .)
  
  find_library(GMOCK_LIBRARY      gmock      PATHS @BINARY_DIR@)
  find_library(GMOCK_MAIN_LIBRARY gmock_main PATHS @BINARY_DIR@)
  find_library(GTEST_LIBRARY      gtest      PATHS @BINARY_DIR@/gtest)
  find_library(GTEST_MAIN_LIBRARY gtest_main PATHS @BINARY_DIR@/gtest)
  
  install(FILES ${GMOCK_LIBRARY}      DESTINATION lib)
  install(FILES ${GMOCK_MAIN_LIBRARY} DESTINATION lib)
  install(FILES ${GTEST_LIBRARY}      DESTINATION lib)
  install(FILES ${GTEST_MAIN_LIBRARY} DESTINATION lib)
]])

# Bandit
execute_process(COMMAND git submodule init   bandit WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
execute_process(COMMAND git submodule update bandit WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

write_config([[
  list(APPEND vendor_include_dirs
    $<BUILD_INTERFACE:@PROJECT_SOURCE_DIR@/bandit>
  )
  install(DIRECTORY @PROJECT_SOURCE_DIR@/bandit/bandit DESTINATION include)
]])
