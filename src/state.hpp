#ifndef STATE_HPP
#define STATE_HPP

#include <vector>
#include <memory>
#include <complex>
#include <ostream>

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

        complex operator[](int i) const {
            assert(i>=0 && i<(1<<nqubits));
            return amplitudes[i];
        }

        int size() const {return 1<<nqubits;}

    private:
        std::unique_ptr<complex[]> amplitudes;
        int nqubits;
};

template<typename T>
std::ostream & operator<<(std::ostream &os, const state<T> &s) {
    os<<"[";
    for (int i=0;i<s.size();i++) {
        os<<s[i];
        if (i<s.size()-1) os<<",";
    }
    os<<"]";
    return os;
}

} // namespace qsim

extern template class qsim::state<double>;
extern template class qsim::state<float>;

#endif // STATE_HPP
