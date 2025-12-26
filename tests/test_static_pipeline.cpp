
#include <slotchain/slotchain.hpp>
#include <cassert>

using namespace slotchain;

int main() {
    signal<int> sig;
    int out = 0;

    sig.connect(make_slot<int>([&](int x){
        out = x;
        return;
    }));

    sig.emit(7);
    assert(out == 7);
}
