bandit_with_gmock
=================

This library is for using [GoogleMock](https://code.google.com/p/googlemock "GoogleMock") by [Bandit](https://github.com/joakimkarlsson/bandit "Bandit"). 

## Examples

```c++
#include <bandit_with_gmock/bandit_with_gmock.hpp>

class hoge {
public:
    void func(bool is_call_func1){
        this->func1();
        this->func2();
    }
    virtual void func1(void) = 0;
    virtual void func2(void) = 0;
};

class hoge_mock: public hoge {
public:
    MOCK_METHOD0(func1, void(void));
    MOCK_METHOD0(func2, void(void));
};

go_bandit([]{
    using namespace bandit;
    
    // describe hoge
    // 	describe #func(bool is_call_func1)
    // 		describe when `is_call_func1` was false
    // 			- it should not call `#func1()` ... FAILED
    // 		describe when `is_call_func1` was true
    // 			- it should call `#func1()` ... OK
    // 
    // There were failures!
    // 
    // hoge #func(bool is_call_func1) when `is_call_func1` was false should not call `#func1()`:
    // src/main.cpp:40: Mock function called more times than expected - returning directly.
    //     Function call: func1()
    //          Expected: to be never called
    //            Actual: called once - over-saturated and active
    // 
    // Test run complete. 2 tests run. 1 succeeded. 1 failed.
    describe("hoge", [&]{
        describe("#func(bool is_call_func1)", [&]{
            describe("when `is_call_func1` was false", [&]{
                it("should not call `#func1()`", [&]{
                    hoge_mock hoge;
                    EXPECT_CALL(hoge, func1()).Times(0);
                    EXPECT_CALL(hoge, func2()).Times(1);
                    hoge.func(false);
                });
            });
            
            describe("when `is_call_func1` was true", [&]{
                it("should call `#func1()`", [&]{
                    hoge_mock hoge;
                    EXPECT_CALL(hoge, func1()).Times(1);
                    EXPECT_CALL(hoge, func2()).Times(1);
                    hoge.func(true);
                });
            });
        });
    });
});

int main(int argc, char * argv[]) {
    return bandit_with_gmock::run(argc, argv);
}
```

## Dependencies

* [GoogleMock](https://code.google.com/p/googlemock "GoogleMock") (ver. 1.7.0)
* [Bandit](https://github.com/joakimkarlsson/bandit "Bandit") (ver. 1.1.4)

## Installation

This library is header-only, so you don't need to build. You should do the steps listed below to install:

### Manual Installation

You should set with the compile options listed below to install manually:

#### Include path

* -I path/to/googlemock/include
* -I path/to/googlemock/gtest/include
* -I path/to/bandit
* -I path/to/bandit\_with\_gmock

#### Library path

* -L path/to/googlemock
* -L path/to/googlemock/gtest

#### Library

* -lgmock
* -lgtest

### Using CMake

If you used CMake, the compile options will be set automatically by writing the content listed below to your project's CMake scripts:

First, you write the content as shown below to the CMake script `CMakeLists.txt` of root directory:

```cmake
cmake_minimum_required(VERSION 3.0.2)

message("Building external...")
try_compile(external_status
  ${PROJECT_BINARY_DIR}/external
  ${PROJECT_SOURCE_DIR}/external
  external
  OUTPUT_VARIABLE external_result
)
if(NOT external_status)
  message("${external_result}")
endif()
message("Built external")
include(${PROJECT_BINARY_DIR}/external/bandit_with_gmock/lib/cmake/bandit_with_gmock.cmake)

link_directories(${PROJECT_BINARY_DIR}/external/bandit_with_gmock/lib)

add_compile_options(-std=c++11)
add_executable(test test.cpp)
target_link_libraries(test bandit_with_gmock::core)
```

Next, you create `external` directory, and write the content shown below to CMake script `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.0.2)

include(ExternalProject)

ExternalProject_Add(bandit_with_gmock
  GIT_REPOSITORY https://github.com/mrk21/bandit_with_gmock.git
  GIT_TAG v1.2.0
  PREFIX bandit_with_gmock
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    -DBUILD_DEPENDENCY=ON
)
```

In addition, if you specified `bandit_with_gmock::main` instead of `bandit_with_gmock::core` to `target_link_libraries()` command, you will not need to write the main function to your test code `test.cpp`. In this case, you should specify `-DBUILD_LIBRARY` CMake option.

`CMakeLists.txt`:

```cmake
...
target_link_libraries(test bandit_with_gmock::main)
```

`external/CMakeLists.txt`:

```cmake
...
ExternalProject_Add(bandit_with_gmock
  GIT_REPOSITORY https://github.com/mrk21/bandit_with_gmock.git
  GIT_TAG v1.2.0
  PREFIX bandit_with_gmock
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    -DBUILD_DEPENDENCY=ON
    -DBUILD_LIBRARY=ON
)
```

## Command line options

Can use GoogleMock and Bandit options.

## Other stuff

* [BDD gmock Aliases](https://github.com/andystanton/gmock-bdd-aliases).
