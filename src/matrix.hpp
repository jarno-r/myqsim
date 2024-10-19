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
        matrix(matrix<T> &&)=default;
        matrix(const matrix<T> &other):matrix(other.nrows,other.ncols) {
            std::copy(other.data.get(),other.data.get()+nrows*ncols,data.get());
        }

        matrix & operator=(matrix<T> &&)=default;

        int rows() const {return nrows;}
        int cols() const {return ncols;}

        T operator()(int row,int col) const {
            assert(row<nrows && col<ncols && row>=0 && col>=0);
            return data[row*ncols+col];
        }

        T & operator()(int row,int col) {
            assert(row<nrows && col<ncols && row>=0 && col>=0);
            return data[row*ncols+col];
        }

        matrix<T> operator*(const matrix<T> &other) const;

        /// @brief Conjugate transpose
        /// @return Conjugate transpose of this matrix
        matrix<T> H() const;

    private:
        int nrows;
        int ncols;
        std::unique_ptr<T[]> data;
};

extern template class matrix<float>;
extern template class matrix<double>;
extern template class matrix<std::complex<float>>;
extern template class matrix<std::complex<double>>;

}

#endif // MATRIX_HPP
