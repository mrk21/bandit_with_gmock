if(NOT BUILD_LIBRARY)
  return()
endif()

add_library(bandit_with_gmock_main ${library_type} main.cpp)
target_link_libraries(bandit_with_gmock_main bandit_with_gmock::core)
set_target_properties(bandit_with_gmock_main PROPERTIES EXPORT_NAME main)

install(TARGETS bandit_with_gmock_main
  DESTINATION lib
  EXPORT bandit_with_gmock
)
