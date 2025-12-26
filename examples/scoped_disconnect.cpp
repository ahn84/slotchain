
#include <slotchain/slotchain.hpp>
#include <iostream>

using namespace slotchain;

int main() {
    signal<int> sig;

    {
        scoped_connection c{sig.connect(
            make_slot<int>([](int x){
                std::cout << x << "\n";
                return;
            })
        )};
        sig.emit(10);
    }

    sig.emit(10); // no output
}
