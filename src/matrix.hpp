#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <memory>
#include <complex>

namespace qsim {
    
template<typename T>
class matrix {
    public:
        matrix()=delete;
        matrix(int rows,int cols);
        matrix(std::initializer_list<std::initializer_list<T>> data);

        T operator()(int row,int col) const {
            assert(row<rows && col<cols && row>=0 && col>=0);
            return data[row*cols+col];
        }

        T & operator()(int row,int col) {
            assert(row<rows && col<cols && row>=0 && col>=0);
            return data[row*cols+col];
        }

        matrix<T> operator*(const matrix<T> &other) const;

    private:
        int rows;
        int cols;
        std::unique_ptr<T[]> data;
};

extern template class matrix<float>;
extern template class matrix<double>;
extern template class matrix<std::complex<float>>;
extern template class matrix<std::complex<double>>;

}

#endif // MATRIX_HPP
