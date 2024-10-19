#include <iostream>

#include "matrix.hpp"
#include "tests.hpp"

using namespace qsim::tests;
using namespace qsim;
using std::cout;
using namespace std::literals::complex_literals;

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

QSIM_TEST(matrix_conjugate) {
    auto a=matrix<std::complex<float>>{
        {1.0f,1.0f-2if},
        {-2.0f+3if,4.0f}};
    
    auto b=a.H();

    test_assert_approx(b(0,0),1.0f);
    test_assert_approx(b(0,1),-2.0f-3if);
    test_assert_approx(b(1,0),1.0f+2if);
    test_assert_approx(b(1,1),4.0f);
}

QSIM_TEST(matrix_transpose) {
    auto a=matrix<float>{
        {1,2},
        {3,4}};
    
    auto b=a.H();

    test_assert_approx(b(0,0),1.0f);
    test_assert_approx(b(0,1),3.0f);
    test_assert_approx(b(1,0),2.0f);
    test_assert_approx(b(1,1),4.0f);
}
