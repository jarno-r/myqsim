#include <iostream>

#include "tests.hpp"

using std::cout;

namespace qsim::tests {

test_def *last_test=nullptr;

static int run_all_tests(test_def *def) {
    if (def) {
        int r=run_all_tests(def->prev);
        cout<<"Running test "<<def->name<<"... ";
        int q;
        try {
            def->func();
        } catch(const test_assert_exception & e) {
            cout<<"FAILED\n";
            cout<<"Assertion failed: "<<e.what()<<"\n";
            return r|1;
        } catch (...) {
            cout<<"CRASHED\n";
            return r|1;
        }
        cout<<"OK\n";
        return r;
    }
    return 0;
}

int run_tests() {
    cout<<"Running tests...\n";

    auto r=run_all_tests(last_test);
    if (r) {
        cout<<"Some tests failed\n";
    } else {
        cout<<"All tests passed\n";
    }

    return r;
} 

} // namespace qsim::tests
