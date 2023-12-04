#pragma once

#include "json_iterator.h"
#include "visitor.h"

class Value {
public:
    virtual ~Value() {}
    virtual std::string toString() = 0;
    virtual JsonIterator * createIterator() = 0;
    virtual void accept(JsonVisitor * visitor) = 0;
    virtual void set(std::string key, Value * value) {}
};
