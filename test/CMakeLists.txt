if(NOT BUILD_TEST)
  return()
endif()

file(GLOB_RECURSE specs *_spec.cpp)

add_executable(spec_runner
  spec_runner.cpp
  ${specs}
)
target_link_libraries(spec_runner bandit_with_gmock::core)

add_custom_target(spec
  COMMAND $<TARGET_FILE:spec_runner> --reporter=spec
  DEPENDS spec_runner
)
foreach(path IN LISTS specs)
  string(REPLACE ${PROJECT_SOURCE_DIR}/test/spec/ "" basepath ${path})
  string(REPLACE _spec.cpp "" basepath ${basepath})
  string(REPLACE / :: name bandit_with_gmock/${basepath})
  
  add_test(
    NAME ${name}
    COMMAND $<TARGET_FILE:spec_runner> --only=${name}
  )
  set_property(TEST ${name} PROPERTY LABELS ${path})
endforeach()
