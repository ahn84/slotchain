
#pragma once
#include "runtime_slot.hpp"
#include <utility>
#include <type_traits>
#include <variant>
namespace slotchain {
template<typename In, typename Out, typename F>
class runtime_slot_impl: public runtime_slot {
    F f;
    [[no_unique_address]] std::conditional_t<std::is_void_v<Out>, std::monostate, Out> out{};
public:
    runtime_slot_impl(F fn):f(std::move(fn)){}
    std::type_index input_type() const noexcept override { return typeid(In); }
    std::type_index output_type() const noexcept override { return typeid(Out); }
    void* invoke(void* in) override {
        In* i=static_cast<In*>(in);
        if constexpr(std::is_void_v<Out>){ f(*i); return nullptr; }
        else { out=f(*i); return &out; }
    }
};
}
