
#pragma once
#include "small_fn.hpp"
#include "runtime_pipeline.hpp"
#include "scoped_connection.hpp"
#include <vector>
namespace slotchain {
template<typename T>
class signal {
    struct entry {
        std::shared_ptr<connection_node> node;
        small_fn<void(T)> fn;
    };
    std::vector<entry> stat_;
    std::vector<runtime_pipeline> run_;
public:
    template<typename P>
    connection connect(P p){
        auto n=std::make_shared<connection_node>();
        stat_.push_back({n, [p,n](T v){ if(n->connected()) p(v); }});
        return connection{n};
    }
    template<typename P>
    scoped_connection connect_scoped(P p){
        return scoped_connection{connect(p)};
    }
    runtime_pipeline& connect_runtime(){
        run_.emplace_back();
        return run_.back();
    }
    void emit(T v){
        for(auto& e:stat_) if(e.node->connected()) e.fn(v);
        for(auto& r:run_) r(v);
    }
};
}
