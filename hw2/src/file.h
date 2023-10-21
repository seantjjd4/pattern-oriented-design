#pragma once

#include <sys/stat.h>
#include <iostream>
#include "node.h"
#include "visitor.h"

class File: public Node {
public:
    File(string path): Node(path) {
        struct stat sb;
        if (lstat(path.c_str(), &sb) != 0) {
            throw ("No such File (wrong path)");
        } else if ((sb.st_mode & S_IFDIR)) {
            throw ("File Constuctor: non-file given (folder)");
        }
    }

    int numberOfFiles() const {
        return 1;
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * visitor) {
        visitor->visitFile(this);
    }
};