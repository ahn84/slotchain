
#include <slotchain/slotchain.hpp>
#include <cassert>

using namespace slotchain;

int main() {
    signal<int> sig;
    int count = 0;

    auto c = sig.connect(make_slot<int>([&](int){
        ++count;
        return;
    }));

    sig.emit(1);
    c.disconnect();
    sig.emit(1);

    assert(count == 1);
}
