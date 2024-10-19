#ifndef TESTS_HPP
#define TESTS_HPP

namespace qsim::tests {

struct test_assert_exception : std::exception {
    const char *what() const noexcept override {
        return "Assertion failed";
    }
};

static void test_assert_approx(double a, double b) {
    if (std::abs(a-b)<1e-3) return;
    throw std::runtime_error("Assertion failed");
}

struct test_def {
    test_def *prev;
    const char *name;
    void (*func)();
};

extern test_def *last_test;

static test_def add_test(void (*test_func)(), test_def *def, const char *test_name) {
    def->prev=last_test;
    last_test=def;
    def->name=test_name;
    def->func=test_func;
    return *def;
}

#define QSIM_TEST(NAME) \
    void test_##NAME(); \
    test_def NAME##_def = add_test(test_##NAME, &NAME##_def, #NAME); \
    void test_##NAME()


} // namespace qsim::tests

#endif //TESTS_HPP
