
#include <slotchain/slotchain.hpp>
#include <iostream>

using namespace slotchain;

int main() {
    signal<int> sig;

    auto& rp = sig.connect_runtime();
    rp.add_slot<int,int>([](int x){ return x + 1; });
    rp.add_slot<int,void>([](int x){
        std::cout << x << "\n";
    });

    sig.emit(5);
}
