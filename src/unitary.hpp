#ifndef UNITARY_HPP
#define UNITARY_HPP

#include <cstddef>
#include <complex>

#include "matrix.hpp"

namespace qsim {

template<typename T>
class unitary {
    public:
        typedef std::complex<T> complex;

        std::size_t size() const {return 1;}
        void transform(const matrix<complex> &v) const {}
};

}

#endif // UNITARY_HPP
