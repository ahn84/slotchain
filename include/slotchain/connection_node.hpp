
#pragma once
#include <atomic>
namespace slotchain {
struct connection_node {
    std::atomic<bool> alive{true};
    void disconnect() noexcept { alive.store(false); }
    bool connected() const noexcept { return alive.load(); }
};
}
