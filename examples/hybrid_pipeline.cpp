
#include <slotchain/slotchain.hpp>
#include <iostream>

using namespace slotchain;

int main() {
    signal<int> sig;

    auto fast =
        make_slot<int>([](int x){ return x * 3; }) |
        make_slot<int>([](int x){ return x - 1; });

    auto& rp = sig.connect_runtime();
    rp.add_static<int,int>(fast);
    rp.add_slot<int,void>([](int x){
        std::cout << x << "\n";
    });

    sig.emit(4); // (4*3)-1 = 11
}
