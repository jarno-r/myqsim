#ifndef UNITARY_HPP
#define UNITARY_HPP

#include <cstddef>
#include <complex>

#include "matrix.hpp"

namespace qsim {

template<typename T>
class unitary {
    public:
        typedef T real;
        typedef std::complex<real> complex;

        unitary(std::initializer_list<std::initializer_list<complex>> values);

        std::size_t size() const {return nqubits;}
        matrix<complex> transform(const matrix<complex> &v) const;

    private:
        matrix<complex> u;
        int nqubits;
};

extern template class unitary<float>;
extern template class unitary<double>;

}

#endif // UNITARY_HPP
