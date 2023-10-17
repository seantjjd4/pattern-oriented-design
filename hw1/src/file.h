#if !defined(FILE_H)
#define FILE_H

#include <string>
#include <cstddef>
#include <stdexcept>

#include "node.h"
#include "null_iterator.h"

using namespace std;

class File: public Node {
public:
    File(string path): _path(path) {
        size_t found = path.find_last_of('/');
        if(found == string::npos || _path.back() == '/') {
            throw invalid_argument("path format error");
        }
        _name = path.substr(found+1);
    }

    ~File() override {}

    string name() const override {
        return _name;
    }

    string path() const override {
        return _path;
    }

    NullIterator * createIterator() override {
        return new NullIterator();
    }


private:
    string _path;
    string _name;
};

#endif // FILE_H
