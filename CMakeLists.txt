cmake_minimum_required(VERSION 2.8)
project(bandit_with_gmock)

message("Building vendor...")
try_compile(vendor_status
  ${PROJECT_BINARY_DIR}/vendor
  ${PROJECT_SOURCE_DIR}/vendor
  vendor
  OUTPUT_VARIABLE vendor_result
)
if(NOT vendor_status)
  message("${vendor_result}")
  return()
endif()
message("Built vendor")

include(${PROJECT_BINARY_DIR}/vendor/cmake/vendor.cmake)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -stdlib=libc++ -Wall -Wextra")
else()
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -Wextra")
endif()

set(LIBS ${vendor_libraries})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${vendor_include_dirs})

if(IS_EXAMPLES)
  add_subdirectory(examples)
else()
  add_subdirectory(test)
endif()
