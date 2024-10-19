#include <iostream>
#include <string>

#include "state.hpp"
#include "run_tests.hpp"

using std::cout;
using namespace qsim;

int main(int argc, char *argv[])
{
    if (argc>1 && std::string(argv[1]) == "test")
        return qsim::tests::run_tests();

    cout<<"Hello, World!\n";

    state<double> s(3);
}
