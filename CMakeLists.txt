cmake_minimum_required(VERSION 2.8)
project(bandit_with_gmock)

option(BUILD_DEPENDENCY "Whether to build the dependencies" OFF)
option(BUILD_LIBRARY "Whether to build the libraries" OFF)
option(BUILD_TEST "Whether to build the tests" OFF)
option(BUILD_EXAMPLE "Whether to build the examples" OFF)

message("Building vendor...")
try_compile(vendor_status
  ${PROJECT_BINARY_DIR}/vendor
  ${PROJECT_SOURCE_DIR}/vendor
  vendor
  CMAKE_FLAGS
    -DBUILD_DEPENDENCY=${BUILD_DEPENDENCY}
    -DBUILD_LIBRARY=${BUILD_LIBRARY}
    -DBUILD_TEST=${BUILD_TEST}
    -DBUILD_EXAMPLE=${BUILD_EXAMPLE}
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

enable_testing()
add_subdirectory(bandit_with_gmock)
add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(examples)
