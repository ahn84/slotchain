
#pragma once
#include "concepts.hpp"

namespace slotchain {
template<typename F, typename G>
struct pipeline {
    F f; G g;
    using input_type = typename slot_traits<F>::input_type;
    using output_type = typename slot_traits<G>::output_type;
    auto operator()(input_type v) const { return g(f(v)); }
};

template<typename F, typename G>
requires chainable<F,G>
auto operator|(F f, G g) { return pipeline<F,G>{f,g}; }
}
