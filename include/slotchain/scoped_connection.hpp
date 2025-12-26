
#pragma once
#include "connection.hpp"
namespace slotchain {
class scoped_connection {
    connection c_;
public:
    scoped_connection() = default;
    explicit scoped_connection(connection c):c_(c){}
    ~scoped_connection(){ c_.disconnect(); }
    scoped_connection(scoped_connection&&)=default;
    scoped_connection& operator=(scoped_connection&&)=default;
    scoped_connection(const scoped_connection&)=delete;
    scoped_connection& operator=(const scoped_connection&)=delete;
};
}
