#include <cassert>
#include <ranges>
#include <numeric>
#include <random>
#include <bit>
#include <algorithm>

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
    for (auto i = 0ULL; i < 1 << nqubits; ) {
        
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

        i++;
        while(mask & i) i += mask & i;
    }
}

template <typename T>
uint64_t state<T>::sample(const std::vector<int> &qubits)
{
    assert(std::all_of(qubits.begin(), qubits.end(), [this](auto q) { return q < nqubits; }));
    auto mask = std::accumulate(qubits.begin(), qubits.end(), 0ULL, 
        [](auto m, auto q) { return m | 1ULL << q; });
    assert(std::popcount(mask)==qubits.size());

    auto probabilities=std::vector<T>(1<<qubits.size());
    for(int i=0;i<1<<nqubits;i++) {
        auto range=std::views::iota(0uz, qubits.size());
        auto k=std::accumulate(range.begin(),range.end(), 0ULL,
            [&](auto k, auto q) { return k | ((i & (1<<qubits[q]))?1:0)<<q; });
        probabilities[k]+=std::norm(amplitudes[i]);
    }

    auto g=std::default_random_engine(std::random_device()());
    auto r=std::uniform_real_distribution<T>(0,1)(g);
    auto p=std::reduce(probabilities.begin(), probabilities.end());
    assert(std::abs(p-1)<1e-3);
    r*=p; // Reduce inaccuracies a bit.

    auto c=0.0f;
    for(int i=0;i<probabilities.size();i++) {
        c+=probabilities[i];
        if(r<=c) return i;
    }
    return probabilities.size()-1;
}

template <typename T>
void state<T>::collapse(const std::vector<int> &qubits, uint64_t value)
{
    assert(std::all_of(qubits.begin(), qubits.end(), [this](auto q) { return q < nqubits; }));
    auto mask = std::accumulate(qubits.begin(), qubits.end(), 0ULL, 
        [](auto m, auto q) { return m | 1ULL << q; });
    assert(std::popcount(mask)==qubits.size());

    auto range=std::views::iota(0uz, qubits.size());
    auto pattern=std::ranges::fold_left(range.begin(),range.end(),0ULL,
        [&](auto p, auto q) { return p | ((value & (1<<q))?1:0)<<qubits[q]; });

    for(int i=0;i<1<<nqubits;i++) {
        if (i&mask!=pattern) {
            amplitudes[i]=0;
        }
    }
    normalize();
}

template <typename T>
void state<T>::normalize() {
    auto r=std::ranges::subrange(amplitudes.get(), amplitudes.get()+(1<<nqubits))
        |std::views::transform([](auto a) { return std::norm(a); });
    auto p=std::reduce(r.begin(),r.end());

    for(int i=0;i<1<<nqubits;i++) {
        amplitudes[i]/=p;
    }
}

}
