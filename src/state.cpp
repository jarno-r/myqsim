#include <cassert>

#include "state.hpp"
#include "matrix.hpp"

namespace qsim {

    template class qsim::state<double>;
    template class qsim::state<float>;

    template <typename T>
    state<T>::state(int qubits)
    {
        nqubits = qubits;
        amplitudes = std::make_unique<complex[]>(1 << nqubits);
        amplitudes[0] = 1;
    }

    template <typename T>
    void state<T>::apply(const unitary<T>& op, const std::vector<int>& qubits)
    {
        assert(qubits.size() == op.size());

        auto mask = 0ULL;
        for (auto q : qubits)
            mask |= 1 << q;

        assert(std::popcount(mask) == qubits.size());
        assert(mask < (1 << nqubits));

        matrix<complex> v(1 << op.size(), 1);
        for (auto i = 0ULL; i < 1 << nqubits; mask & (++i) ? i += mask & i : 0) {
            
            auto pack = [qubits](auto f) {
                for (auto j = 0ULL; j < 1 << qubits.size(); j++) {
                    auto p = 0ULL;
                    for (int k = 0; k < qubits.size(); k++)
                        p |= (j & (1 << k)) ? (1ULL << qubits[k]) : 0;
                    f(j, p);
                }
            };

            pack([&](auto j, auto p) { v(j, 0) = amplitudes[i + p]; });

            v=op.transform(v);

            pack([&](auto j, auto p) { amplitudes[i + p]=v(j,0); });
        }
    }

}
