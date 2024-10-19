#include "matrix.hpp"

namespace qsim {

template<typename T>
matrix<T>::matrix(int rows, int cols) :
    rows(rows), cols(cols), data(std::make_unique<T[]>(rows* cols)) {}

template<typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> values) :
    rows(values.size()),
    cols(std::empty(values)?0:values.begin()->size()),
    data(std::make_unique<T[]>(rows* cols))
{
    assert(rows > 0 && cols > 0);
    int i = 0;
    for (auto& row : values) {
        assert(row.size() == cols);
        for (auto& elem : row) {
            data[i++] = elem;
        }
    }
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &other) const {
    assert(cols == other.rows);
    matrix<T> result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            T sum = 0;
            for (int k = 0; k < cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

template class matrix<float>;
template class matrix<double>;
template class matrix<std::complex<float>>;
template class matrix<std::complex<double>>;
    
}
