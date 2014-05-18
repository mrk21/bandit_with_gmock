set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
add_executable(base base/main.cpp)
target_link_libraries(base ${LIBS})
