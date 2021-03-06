/*!
 * bandit_with_gmock
 * Copyright (c) 2013 Yuichi MURATA
 */

#ifndef __INCLUDED_BANDIT_WITH_GMOCK_HPP__
#define __INCLUDED_BANDIT_WITH_GMOCK_HPP__

#include <bandit/bandit.h>
#include <gmock/gmock.h>

namespace bandit_with_gmock {
    class listener_adapter: public testing::EmptyTestEventListener, public bandit::detail::listener {
    protected:
        bandit::detail::listener * base;
        bandit::detail::assertion_exception * exception{nullptr};
        
    public:
        listener_adapter(bandit::detail::listener * base) : base(base) {}
        
        bool is_faild_mock() const {
            return this->exception != nullptr;
        }
        
        void clear_mock_error() {
            if (this->exception != nullptr) {
                delete this->exception;
                this->exception = nullptr;
            }
        }
        
        
        // bandit listener APIs
        virtual void test_run_starting(void) {
            this->base->test_run_starting();
        }
        
        virtual void test_run_complete(void) {
            this->base->test_run_complete();
        }
        
        virtual void context_starting(const char * desc) {
            this->base->context_starting(desc);
        }
        
        virtual void context_ended(const char * desc) {
            this->base->context_ended(desc);
        }
        
        virtual void test_run_error(const char * desc, const bandit::detail::test_run_error & error) {
            this->base->test_run_error(desc, error);
        }
        
        virtual void it_starting(const char * desc) {
            this->clear_mock_error();
            this->base->it_starting(desc);
        }
        
        virtual void it_succeeded(const char * desc) {
            if (this->exception != nullptr) throw *this->exception;
            this->base->it_succeeded(desc);
        }
        
        virtual void it_failed(const char * desc, const bandit::detail::assertion_exception & ex) {
            this->base->it_failed(desc, ex);
        }
        
        virtual void it_unknown_error(const char * desc) {
            this->base->it_unknown_error(desc);
        }
        
        virtual void it_skip(const char* desc) {
            this->base->it_skip(desc);
        }
        
        virtual bool did_we_pass() const {
            return this->base->did_we_pass();
        }
        
        
        // GoogleTest listener APIs
        virtual void OnTestPartResult(const testing::TestPartResult & result) {
            if (!result.failed() || this->exception != nullptr) return;
            this->exception = new bandit::detail::assertion_exception(result.summary(), result.file_name(), result.line_number());
        }
    };
    
    inline listener_adapter & listener() {
        return static_cast<listener_adapter &>(bandit::detail::registered_listener());
    }
    
    inline int run(int argc, char * argv[]) {
        bandit::detail::options opt(argc, argv);
        bandit::detail::failure_formatter_ptr formatter(bandit::detail::create_formatter(opt));
        bandit::detail::colorizer colorizer(!opt.no_color());
        bandit::detail::listener_ptr reporter(bandit::detail::create_reporter(opt, formatter.get(), colorizer));
        
        listener_adapter * listener = new listener_adapter(reporter.get());
        bandit::detail::registered_listener(listener);
        
        bandit::detail::run_policy_ptr run_policy = create_run_policy(opt);
        registered_run_policy(run_policy.get());
        
        testing::InitGoogleMock(&argc, argv);
        
        auto & gtest_listeners = testing::UnitTest::GetInstance()->listeners();
        delete gtest_listeners.Release(gtest_listeners.default_result_printer());
        gtest_listeners.Append(listener);
        
        return bandit::run(opt, bandit::detail::specs(), bandit::detail::context_stack(), *listener);
    }
}

#endif
