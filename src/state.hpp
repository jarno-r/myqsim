#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <memory>
#include <complex>

#include "unitary.hpp"

namespace qsim {

template<typename T>
class state {
    public:
        typedef std::complex<T> complex;

        /// @brief Initialize state to |000...0>
        /// @param qubits Number of qubits
        state(int qubits);

        void apply(const unitary<T> &op, const std::vector<int> &qubits);

    private:
        std::unique_ptr<complex[]> amplitudes;
        int nqubits;
};

} // namespace qsim

extern template class qsim::state<double>;
extern template class qsim::state<float>;

#endif // STATE_HPP
