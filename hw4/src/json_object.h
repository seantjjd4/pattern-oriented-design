#pragma once

#include <map>

#include "value.h"
#include "json_iterator.h"
#include "visitor.h"
#include <iostream>

class JsonObject : public Value {
public:
    JsonObject() {}

    std::string toString() {
        std::string result;
        result += "{\n";
        JsonIterator * it = createIterator();

        for (it->first(); !it->isDone();) {

            result += "\"" + it->currentKey() + "\":" + it->currentValue()->toString();
            it->next();
            if (!it->isDone()) {
                result += ",\n";
            }
        }

        result += "\n}";
        return result;
    }

    void set(std::string key, Value * value) {
        _subValues[key] = value;
    }

    Value * getValue(std::string key) {
        if (_subValues.count(key) > 0) {
            return _subValues[key];
        } else {
            throw "Key not found!";
        }
    }

    JsonIterator * createIterator() {
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor * visitor) {
        visitor->visitJsonObject(this);
    }

    class JsonObjectIterator : public JsonIterator {
    public:
        JsonObjectIterator(JsonObject * jsonObject): _jsonObject(jsonObject) {}

        void first() override {
            _it = _jsonObject->_subValues.begin();
        }

        std::string currentKey() const override {
            return _it->first;
        }

        Value * currentValue() const override {
            return _it->second;
        }

        void next() override {
            _it++;
        }

        bool isDone() const override {
            return _it == _jsonObject->_subValues.end();
        }

    private:
        JsonObject * _jsonObject;
        std::map<std::string, Value *>::iterator _it;
    };

private:
    std::map<std::string, Value *> _subValues;
};
