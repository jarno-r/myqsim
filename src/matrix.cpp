#include "matrix.hpp"

namespace qsim {

template<typename T>
matrix<T>::matrix(int rows, int cols) :
    nrows(rows), ncols(cols), data(std::make_unique<T[]>(rows* cols)) {}

template<typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> values) :
    nrows(values.size()),
    ncols(std::empty(values)?0:values.begin()->size()),
    data(std::make_unique<T[]>(nrows* ncols))
{
    assert(nrows > 0 && ncols > 0);
    int i = 0;
    for (auto& row : values) {
        assert(row.size() == ncols);
        for (auto& elem : row) {
            data[i++] = elem;
        }
    }
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &other) const {
    assert(ncols == other.nrows);
    matrix<T> result(nrows, other.ncols);
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < other.ncols; j++) {
            T sum = 0;
            for (int k = 0; k < ncols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}


template<typename T> static std::complex<T> conjugate(std::complex<T> a) {
    return std::conj(a);
}
static float conjugate(float a) {
    return a;
}
static double conjugate(double a) {
    return a;
}


template<typename T>
matrix<T> matrix<T>::H() const {
    matrix<T> result(ncols, nrows);
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            result(j, i) = conjugate((*this)(i, j));
        }
    }
    return result;
}

template class matrix<float>;
template class matrix<double>;
template class matrix<std::complex<float>>;
template class matrix<std::complex<double>>;
    
}
