
#include <slotchain/slotchain.hpp>
#include <cassert>

using namespace slotchain;

int main() {
    signal<int> sig;
    int out = 0;

    auto& rp = sig.connect_runtime();
    rp.add_slot<int,int>([](int x){ return x * 2; });
    rp.add_slot<int,void>([&](int x){ out = x; });

    sig.emit(4);
    assert(out == 8);
}
