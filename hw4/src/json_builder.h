#pragma once

#include <stack>
#include <utility>

#include "json_object.h"
#include "string_value.h"

class JsonBuilder {
public:
    JsonBuilder() {
        _jsonObject = new JsonObject;
    }

    void buildValue(std::string key, std::string value) {
        StringValue * s = new StringValue(value);
        if (!_storedValues.empty()) {
            std::get<1>(_storedValues.top())->set(key, s);
        } else {
            _jsonObject->set(key, s);
        }
    }

    void buildObject(std::string key) {
        if (key != "") {
            std::pair <std::string, Value *> p (key, new JsonObject);
            _storedValues.push(p);
        }
    }

    void endObject() {
        if (!_storedValues.empty()) {
            auto v = _storedValues.top();
            _storedValues.pop();

            if (!_storedValues.empty()) {
                std::get<1>(_storedValues.top())->set(std::get<0>(v), std::get<1>(v));
            } else {
                _jsonObject->set(std::get<0>(v), std::get<1>(v));
            }
        }
    }

    JsonObject * getJsonObject() {
        return _jsonObject;
    }

private:
    JsonObject * _jsonObject;
    std::stack<std::pair<std::string, Value *>> _storedValues;
};
