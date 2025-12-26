
#pragma once
#include <utility>
#include <type_traits>

namespace slotchain {
template<typename In, typename Out, typename F>
struct slot {
    using input_type = In;
    using output_type = Out;
    F func;
    Out operator()(In v) const { return func(v); }
};

template<typename In, typename F>
slot(F) -> slot<In, std::invoke_result_t<F,In>, F>;

template<typename In, typename F>
auto make_slot(F f) {
    return slot<In, std::invoke_result_t<F,In>, F>{f};
}
}
