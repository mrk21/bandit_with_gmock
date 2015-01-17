#include <bandit_with_gmock/bandit_with_gmock.hpp>

namespace bandit_with_gmock {
go_bandit([]{
    using namespace bandit;
    
    describe("bandit_with_gmock::listener_adapter", [&]{
        describe("#is_faild_mock()", [&]{
            describe("When it was successful in assertion of the mock", [&]{
                it("should be false", [&]{
                    {
                        struct {
                            MOCK_METHOD0(func, void(void));
                        } mock;
                        EXPECT_CALL(mock, func()).Times(1);
                        mock.func();
                    }
                    AssertThat(listener().is_faild_mock(), Equals(false));
                    listener().clear_mock_error();
                });
            });
            
            describe("When it was fail in assertion of the mock", [&]{
                it("should be true", [&]{
                    {
                        struct {
                            MOCK_METHOD0(func, void(void));
                        } mock;
                        EXPECT_CALL(mock, func()).Times(1);
                        mock.func();
                        mock.func();
                    }
                    AssertThat(listener().is_faild_mock(), Equals(true));
                    listener().clear_mock_error();
                });
                
                describe("In the destructor", [&]{
                    it("should be true", [&]{
                        {
                            struct {
                                MOCK_METHOD0(func, void(void));
                            } mock;
                            EXPECT_CALL(mock, func()).Times(1);
                        }
                        AssertThat(listener().is_faild_mock(), Equals(true));
                        listener().clear_mock_error();
                    });
                });
            });
        });
    });
});
}
