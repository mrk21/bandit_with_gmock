cmake_minimum_required(VERSION 2.8)
project(bandit_with_gmock)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -stdlib=libc++ -Wall -Wextra")
set(LIBS pthread gtest gmock)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/vendor/bandit)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/gtest/include)

link_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock)
link_directories(${PROJECT_SOURCE_DIR}/vendor/googlemock/gtest)

add_subdirectory(examples)
