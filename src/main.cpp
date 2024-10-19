#include <iostream>
#include <string>
#include <random>

#include "state.hpp"
#include "run_tests.hpp"

using std::cout;
using namespace qsim;

void superdense();

int main(int argc, char *argv[])
{
    if (argc>1 && std::string(argv[1]) == "test")
        return qsim::tests::run_tests();

    cout<<"Hello, Quantum World!\n";

    superdense();
}

void superdense() {
    state<float> s(2);
    auto sq2inv=1.0f/std::sqrt(2.0f);
    auto h=unitary<float>{{sq2inv,sq2inv},{sq2inv,-sq2inv}};
    auto cx=unitary<float>{{1,0,0,0},{0,1,0,0},{0,0,0,1},{0,0,1,0}};
    auto x=unitary<float>{{0,1},{1,0}};
    auto z=unitary<float>{{1,0},{0,-1}};
    
    auto g=std::default_random_engine(std::random_device()());
    int msg=std::uniform_int_distribution(0,3)(g);

    cout<<"Alice's message: "<<msg<<"\n";
    s.apply(h,{0});
    s.apply(cx,{1,0});

    cout << s << "\n";

    switch(msg) {
        case 0:
            break;
        case 1:
            s.apply(x,{0});
            break;
        case 2:
            s.apply(z,{0});
            break;
        case 3:
            s.apply(x,{0});
            s.apply(z,{0});
            break;
    }

    s.apply(cx,{1,0});
    s.apply(h,{0});

    cout << s << "\n";


}
