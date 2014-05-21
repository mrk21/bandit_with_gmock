file(GLOB_RECURSE SRCS "spec/*_spec.cpp")
add_executable(spec spec.cpp ${SRCS})
target_link_libraries(spec ${LIBS})
