#pragma once

#include "value.h"
#include "json_iterator.h"
#include "visitor.h"

class StringValue : public Value {
public:
    StringValue(std::string str): _str(str) {
    }

    std::string toString() {
        return "\"" + _str + "\"";
    }

    JsonIterator * createIterator() override {
        return new NullIterator();
    }

    void accept(JsonVisitor * visitor) {
        visitor->visitStringValue(this);
    }

private:
    std::string _str;
};
