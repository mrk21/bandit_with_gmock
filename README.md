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


## Compiler options

### Include path

* -I path/to/googlemock/include
* -I path/to/googlemock/gtest/include
* -I path/to/bandit
* -I path/to/bandit_with_gmock

### Library path

* -L path/to/googlemock
* -L path/to/googlemock/gtest

### Library

* -lgmock
* -lgtest
* -lpthread

## Command line options

Can use GoogleMock and Bandit options.

## Other stuff

* [BDD gmock Aliases](https://github.com/andystanton/gmock-bdd-aliases).
