cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(vendor_cmake_path ${PROJECT_BINARY_DIR}/cmake/vendor.cmake)
file(WRITE ${vendor_cmake_path} "
  set(vendor_include_dirs
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
  )
  unset(vendor_libraries)
")

if(NOT BUILD_DEPENDENCY AND NOT BUILD_LIBRARY)
  return()
endif()

# Google Mock
ExternalProject_Add(google_mock
  SVN_REPOSITORY http://googlemock.googlecode.com/svn/tags/release-1.7.0
  INSTALL_COMMAND ""
  UPDATE_COMMAND ""
)
ExternalProject_Get_Property(google_mock BINARY_DIR)
ExternalProject_Get_Property(google_mock SOURCE_DIR)

file(APPEND ${vendor_cmake_path} "
  list(APPEND vendor_include_dirs
    $<BUILD_INTERFACE:${SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${SOURCE_DIR}/gtest/include>
  )
  link_directories(
    ${BINARY_DIR}
    ${BINARY_DIR}/gtest
  )
  list(APPEND vendor_libraries
    gmock
    gtest
  )
  
  install(DIRECTORY ${SOURCE_DIR}/include DESTINATION .)
  install(DIRECTORY ${SOURCE_DIR}/gtest/include DESTINATION .)
  install(FILES ${BINARY_DIR}/libgmock.a DESTINATION lib)
  install(FILES ${BINARY_DIR}/libgmock_main.a DESTINATION lib)
  install(FILES ${BINARY_DIR}/gtest/libgtest.a DESTINATION lib)
  install(FILES ${BINARY_DIR}/gtest/libgtest_main.a DESTINATION lib)
")

# Bandit
execute_process(COMMAND git submodule init   bandit WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
execute_process(COMMAND git submodule update bandit WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

file(APPEND ${vendor_cmake_path} "
  list(APPEND vendor_include_dirs
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/bandit>
  )
  install(DIRECTORY ${PROJECT_SOURCE_DIR}/bandit/bandit DESTINATION include)
")
