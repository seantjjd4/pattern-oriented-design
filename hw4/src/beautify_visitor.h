#pragma once

#include <string>
#include "./visitor.h"
#include "./json_object.h"
#include "./string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:
    BeautifyVisitor() {
        _level = 0;
    }

    void visitJsonObject(JsonObject * obj) {
        _result += "{\n";
        auto it = obj->createIterator();
        _level++;
        for(it->first(); !it->isDone();) {
            for (int i = 0; i < _level; i++) {
                _result += "    ";
            }
            _result += "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);

            it->next();
            if (!it->isDone()) {
                _result += ",\n";
            }
        }
        _level--;
        _result += "\n";
        for (int i = 0; i < _level; i++) {
            _result += "    ";
        }
        _result += "}";

    }

    void visitStringValue(StringValue * val) {
        _result += val->toString();
    }

    std::string getResult() const {
        return _result;
    }

private:
    int _level;
    std::string _result;
};