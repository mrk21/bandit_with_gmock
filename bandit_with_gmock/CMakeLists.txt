add_library(bandit_with_gmock INTERFACE)

target_include_directories(bandit_with_gmock INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  ${vendor_include_dirs}
)
target_link_libraries(bandit_with_gmock INTERFACE
  ${vendor_libraries}
)

install(TARGETS bandit_with_gmock
  DESTINATION lib
  EXPORT bandit_with_gmock
)
install(EXPORT bandit_with_gmock
  DESTINATION lib/cmake
  NAMESPACE bandit_with_gmock::
)
install(DIRECTORY .
  DESTINATION include/bandit_with_gmock
  PATTERN CMakeLists.txt EXCLUDE
)
