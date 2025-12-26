
#pragma once
#include <type_traits>
#include <concepts>

namespace slotchain {
template<typename In, typename Out, typename F> struct slot;

template<typename T> struct slot_traits;

template<typename In, typename Out, typename F>
struct slot_traits<slot<In,Out,F>> {
    using input_type = In;
    using output_type = Out;
};

template<typename A, typename B>
concept chainable =
    std::same_as<typename slot_traits<A>::output_type,
                 typename slot_traits<B>::input_type>;
}
