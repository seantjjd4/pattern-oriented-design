#pragma once

#include "visitor.h"
#include "file.h"
#include "folder.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _name(name) {};

    void visitFile(File * file) {
        if (file->name() == _name) {
            _pathList.push_back(file->path());
        }
    }

    void visitFolder(Folder * folder) {
        if (folder->name() == _name) {
            _pathList.push_back(folder->path());
        }
        auto it = folder->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    }

    std::list<string> getPaths() const {
        return _pathList;
    }

private:
    std::string _name;
    std::list<string> _pathList;
};