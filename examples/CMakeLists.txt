add_custom_target(examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
add_executable(base base/main.cpp)
target_link_libraries(base ${LIBS})
add_dependencies(examples base)
