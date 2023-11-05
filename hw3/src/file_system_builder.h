#pragma once

#include <string>

#include "node.h"
#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const {
        return _root;
    }

    void buildFile(string path) {
        Node * file = new File(path);
        if (_folders.empty()) {
            _root->add(file);
        } else {
            _folders.top()->add(file);
        }
    }

    void buildFolder(string path) {
        Folder * folder = new Folder(path);
        _folders.push(folder);
    }

    void endFolder() {
        if (!_folders.empty()) {
            Folder * folder = _folders.top();
            _folders.pop();
            if (_folders.empty()) {
                _root->add(folder);
            } else {
                _folders.top()->add(folder);
            }
        }
    }

    void setRoot(string rootPath) {
        _root = new Folder(rootPath);
    }

private:
    Folder * _root;
    std::stack<Folder *> _folders;
};
