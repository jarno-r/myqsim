#ifndef TESTS_HPP
#define TESTS_HPP

namespace qsim::tests {

struct test_assert_exception : std::exception {
    test_assert_exception(const char *file, int line, const char *msg) :
    msg(std::string(file)+":"+std::to_string(line)+": "+msg+" failed!") {}

    const char *what() const noexcept override {
        return msg.c_str();
    }

    private:
        std::string msg;
};

template<typename A,typename B>
static bool test_assert_approx(A a, B b) {
    return (std::abs(a-b)<1e-3);
}

static void test_assert_msg(bool cond, const char *file, int line, const char *msg) {
    if (cond) return;
    throw test_assert_exception(file,line,msg);
}

#define test_assert_approx(a,b) test_assert_msg(test_assert_approx(a,b),__FILE__,__LINE__,"test_assert_approx("#a","#b")")

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
