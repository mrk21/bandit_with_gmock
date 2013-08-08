/*!
 * bandit_with_gmock
 * Copyright (c) 2013 Yuichi MURATA
 */

#ifndef __INCLUDED_BANDIT_WITH_GMOCK_HPP__
#define __INCLUDED_BANDIT_WITH_GMOCK_HPP__

#include <bandit/bandit.h>
#include <gmock/gmock.h>

namespace bandit_with_gmock {
  class listener_adapter: public testing::EmptyTestEventListener, public bandit::listener {
  protected:
    bandit::listener * base;
    bool is_failed;
    
  public:
    listener_adapter(bandit::listener * base) : base(base), is_failed(false) {}
    
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
    
    virtual void test_run_error(const char * desc, const bandit::test_run_error & error) {
      this->base->test_run_error(desc, error);
    }
    
    virtual void it_starting(const char * desc) {
      this->is_failed = false;
      this->base->it_starting(desc);
    }
    
    virtual void it_succeeded(const char * desc) {
      this->base->it_succeeded(desc);
    }
    
    virtual void it_failed(const char * desc, const bandit::assertion_exception & ex) {
      this->base->it_failed(desc, ex);
    }
    
    virtual void it_unknown_error(const char * desc) {
      this->base->it_unknown_error(desc);
    }
    
    virtual bool did_we_pass() const {
      return this->base->did_we_pass();
    }
    
    virtual void OnTestPartResult(const testing::TestPartResult & result) {
      if (!result.failed() || this->is_failed) return;
      this->is_failed = true;
      throw bandit::assertion_exception(result.summary(), result.file_name(), result.line_number());
    }
  };
  
  int run(int argc, char * argv[]) {
    bandit::options opt(argc, argv);
    bandit::failure_formatter_ptr formatter(bandit::create_formatter(opt));
    bandit::detail::colorizer colorizer(!opt.no_color());
    bandit::listener_ptr reporter(bandit::create_reporter(opt, formatter.get(), colorizer));
    
    listener_adapter * listener = new listener_adapter(reporter.get());
    bandit::registered_listener(listener);
    
    testing::InitGoogleMock(&argc, argv);
    
    auto & gtest_listeners = testing::UnitTest::GetInstance()->listeners();
    delete gtest_listeners.Release(gtest_listeners.default_result_printer());
    gtest_listeners.Append(listener);
    
    return bandit::run(opt, bandit::detail::specs(), bandit::context_stack(), *listener);
  }
}

#endif
