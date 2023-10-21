#pragma once

#include <list>
#include <sys/stat.h>
#include <iostream>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"
#include "visitor.h"

using namespace std;

class Folder: public Node {

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite):_host(composite) {
        _version = _host->_getVersion();
    };
        ~FolderIterator() {}
        void first() {
            if (_host->_getVersion() != _version) {
                throw ("Iterator unavailable! -> --Folder structure changed--");
            }
            _current = _host->_nodes.begin();
        };

        Node * currentItem() const {
            return *_current;
        };

        void next() {
            if (_host->_getVersion() != _version) {
                throw ("Iterator unavailable! -> --Folder structure changed--");
            }
            _current++;
        };
        bool isDone() const {
            return _current == _host->_nodes.end();
        };

    private:
        Folder* const _host;
        int _version;
        std::list<Node *>::iterator _current;
    };

private:
    list<Node *> _nodes;
    int _version = 0;

    int _getVersion() {
        return _version;
    }

protected:
    void removeChild(Node * target) {
        _nodes.remove(target);
    }

public:
    Folder(string path): Node(path) {
        struct stat sb;
        if (lstat(path.c_str(), &sb) != 0) {
            throw ("No such Folder (wrong path)");
        } else if (!(sb.st_mode & S_IFDIR)) {
            throw ("Folder Constuctor: non-folder given");
        }
    }

    void add(Node * node) {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);

        // version control for iterator throwing exception when sturcture changed
        _version++;
    }

    Node * getChildByName(const char * name) const {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }
        return nullptr;
    }

    int numberOfFiles() const {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() {
        return new FolderIterator(this);
    }

    Iterator * dfsIterator() {
        return new DfsIterator(this);
    }

    Node * find(string path) {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
        // version control for iterator throwing exception when sturcture changed
        _version++;
    }

    void accept(Visitor * visitor) {
        visitor->visitFolder(this);
    }
};