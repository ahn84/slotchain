
#pragma once
#include <typeindex>
#include <memory>
namespace slotchain {
struct runtime_slot {
    virtual ~runtime_slot()=default;
    virtual std::type_index input_type() const noexcept=0;
    virtual std::type_index output_type() const noexcept=0;
    virtual void* invoke(void*)=0;
};
using runtime_slot_ptr = std::unique_ptr<runtime_slot>;
}
