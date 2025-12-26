#pragma once
#include <cstddef>
#include <cstdint>
#include <new>
#include <type_traits>
#include <utility>
#include <functional>

namespace slotchain {

template<typename Sig, std::size_t StorageBytes = 64,
         std::size_t StorageAlign = alignof(std::max_align_t)>
class small_fn;

template<typename R, typename... Args, std::size_t StorageBytes, std::size_t StorageAlign>
class small_fn<R(Args...), StorageBytes, StorageAlign> {
public:
    small_fn() noexcept = default;
    small_fn(std::nullptr_t) noexcept {}

    small_fn(const small_fn& other) { other.clone_into(*this); }
    small_fn& operator=(const small_fn& other) {
        if (this != &other) { reset(); other.clone_into(*this); }
        return *this;
    }

    small_fn(small_fn&& other) noexcept { other.move_into(*this); }
    small_fn& operator=(small_fn&& other) noexcept {
        if (this != &other) { reset(); other.move_into(*this); }
        return *this;
    }

    ~small_fn() { reset(); }

    template<typename F>
    small_fn(F f) { emplace(std::move(f)); }

    template<typename F>
    void emplace(F f) {
        using Fn = std::decay_t<F>;
        static_assert(sizeof(Fn) <= StorageBytes,
            "slotchain::small_fn: callable too large for SBO storage");
        static_assert(alignof(Fn) <= StorageAlign,
            "slotchain::small_fn: callable alignment too strict");

        reset();
        new (storage_) Fn(std::move(f));

        invoke_ = [](void* self, Args... args)->R {
            return (*static_cast<Fn*>(self))(std::forward<Args>(args)...);
        };
        destroy_ = [](void* self) noexcept {
            static_cast<Fn*>(self)->~Fn();
        };
        clone_ = [](const void* self, void* dst) {
            new (dst) Fn(*static_cast<const Fn*>(self));
        };
        move_ = [](void* self, void* dst) noexcept {
            new (dst) Fn(std::move(*static_cast<Fn*>(self)));
            static_cast<Fn*>(self)->~Fn();
        };
    }

    void reset() noexcept {
        if (destroy_) destroy_(storage_);
        invoke_ = nullptr; destroy_ = nullptr;
        clone_ = nullptr; move_ = nullptr;
    }

    explicit operator bool() const noexcept { return invoke_ != nullptr; }

    R operator()(Args... args) const {
        if (!invoke_) throw std::bad_function_call{};
        return invoke_(const_cast<void*>(static_cast<const void*>(storage_)),
                       std::forward<Args>(args)...);
    }

private:
    alignas(StorageAlign) std::byte storage_[StorageBytes]{};
    using invoke_t  = R(*)(void*, Args...);
    using destroy_t = void(*)(void*) noexcept;
    using clone_t   = void(*)(const void*, void*);
    using move_t    = void(*)(void*, void*) noexcept;

    invoke_t  invoke_  = nullptr;
    destroy_t destroy_ = nullptr;
    clone_t   clone_   = nullptr;
    move_t    move_    = nullptr;

    void clone_into(small_fn& dst) const {
        if (!invoke_) return;
        dst.invoke_ = invoke_; dst.destroy_ = destroy_;
        dst.clone_ = clone_; dst.move_ = move_;
        clone_(storage_, dst.storage_);
    }

    void move_into(small_fn& dst) noexcept {
        if (!invoke_) return;
        dst.invoke_ = invoke_; dst.destroy_ = destroy_;
        dst.clone_ = clone_; dst.move_ = move_;
        move_(storage_, dst.storage_);
        reset();
    }
};

} // namespace slotchain
