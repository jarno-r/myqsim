#include <iostream>

#include "matrix.hpp"
#include "tests.hpp"

using namespace qsim::tests;
using namespace qsim;
using std::cout;

QSIM_TEST(matrix_init) {
    auto a=matrix<float>{{1,2},{3,4}};

    test_assert_approx(a(0,0),1);
    test_assert_approx(a(0,1),2);
    test_assert_approx(a(1,0),3);
    test_assert_approx(a(1,1),4);
}

QSIM_TEST(matrix_mult) {
    auto a=matrix<float>{
        {1,2,3},
        {4,5,6}};
    auto b=matrix<float>{
        {1,2},
        {3,4},
        {5,6}};

    auto c=a*b;

    test_assert_approx(c(0,0),22);
    test_assert_approx(c(0,1),28);
    test_assert_approx(c(1,0),49);
    test_assert_approx(c(1,1),64);
}
