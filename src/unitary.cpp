#include <bit>

#include "unitary.hpp"

namespace qsim {

template<typename T>
unitary<T>::unitary(std::initializer_list<std::initializer_list<complex>> data) : u(data) {
    nqubits=std::bit_width((uint)u.rows())-1;
    assert(u.rows()==u.cols());
    assert(u.rows()==1<<nqubits);
    auto c=u*u.H();
    for (int i=0;i<c.rows();i++)
        for (int j=0;j<c.cols();j++)
            assert(std::abs(c(i,j)-((i==j)?T(1):T(0)))<1e-3);
}

template<typename T>
matrix<std::complex<T>> unitary<T>::transform(const matrix<complex> &v) const
{
    assert(v.cols()==1);
    assert(v.rows()==1<<size());

    return u*v;
}

template class unitary<float>;
template class unitary<double>;


}