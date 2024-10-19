#include <iostream>

#include "state.hpp"
#include "tests.hpp"

using namespace qsim::tests;
using namespace qsim;

QSIM_TEST(state_not_1) {
    auto s=state<float>(1);
    s.apply(unitary<float>{{0,1},{1,0}}, {0});
    test_assert_approx(s[0],0.0f);
    test_assert_approx(s[1],1.0f);
}

QSIM_TEST(state_not_2) {
    auto s=state<float>(2);
    s.apply(unitary<float>{{0,1},{1,0}}, {1});
    test_assert_approx(s[0],0.0f);
    test_assert_approx(s[1],0.0f);
    test_assert_approx(s[2],1.0f);
    test_assert_approx(s[3],0.0f);
}
