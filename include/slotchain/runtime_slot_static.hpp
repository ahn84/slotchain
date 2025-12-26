
#pragma once
#include "runtime_slot.hpp"
namespace slotchain {
template<typename In, typename Out, typename Pipeline>
class runtime_slot_static: public runtime_slot {
    Pipeline p; Out out{};
public:
    runtime_slot_static(Pipeline pp):p(std::move(pp)){}
    std::type_index input_type() const noexcept override { return typeid(In); }
    std::type_index output_type() const noexcept override { return typeid(Out); }
    void* invoke(void* in) override {
        In* i=static_cast<In*>(in);
        if constexpr(std::is_void_v<Out>){ p(*i); return nullptr; }
        else { out=p(*i); return &out; }
    }
};
}
