
#pragma once
#include <memory>
#include "connection_node.hpp"

namespace slotchain {
class connection {
    std::weak_ptr<connection_node> node_;
public:
    connection() = default;
    explicit connection(std::weak_ptr<connection_node> n):node_(n){}
    void disconnect(){ if(auto n=node_.lock()) n->disconnect(); }
    bool connected() const {
        if(auto n=node_.lock()) return n->connected();
        return false;
    }
};
}
