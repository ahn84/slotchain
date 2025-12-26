
#include <slotchain/slotchain.hpp>
#include <iostream>

using namespace slotchain;

int main() {
    signal<int> sig;

    auto pipe =
        make_slot<int>([](int x){ return x * 2; }) |
        make_slot<int>([](int x){
            std::cout << x << "\n";
            return;
        });

    sig.connect(pipe);
    sig.emit(21);
}
