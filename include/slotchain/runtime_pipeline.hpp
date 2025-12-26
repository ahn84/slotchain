
#pragma once
#include "runtime_slot_impl.hpp"
#include "runtime_slot_static.hpp"
#include "connection.hpp"
#include "connection_node.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

namespace slotchain {
class runtime_pipeline {
    std::shared_ptr<connection_node> node_=std::make_shared<connection_node>();
    std::vector<runtime_slot_ptr> slots_;
public:
    template<typename In, typename Out, typename F>
    void add_slot(F f){
        auto s=std::make_unique<runtime_slot_impl<In,Out,F>>(std::move(f));
        if(!slots_.empty() && slots_.back()->output_type()!=s->input_type())
            throw std::logic_error("incompatible slot");
        slots_.push_back(std::move(s));
    }
    template<typename In, typename Out, typename Pipeline>
    void add_static(Pipeline p){
        auto s=std::make_unique<runtime_slot_static<In,Out,Pipeline>>(std::move(p));
        if(!slots_.empty() && slots_.back()->output_type()!=s->input_type())
            throw std::logic_error("incompatible slot");
        slots_.push_back(std::move(s));
    }
    template<typename T>
    void operator()(T v){
        if(!node_->connected()) return;
        void* cur=&v;
        for(auto& s:slots_) cur=s->invoke(cur);
    }
    connection get_connection() const { return connection{node_}; }
};
}
