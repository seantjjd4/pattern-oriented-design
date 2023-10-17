#if !defined(FOLDER)
#define FOLDER

#include <string>
#include <list>
#include <cstddef>
#include <stdexcept>

#include "node.h"
#include "iterator.h"

using namespace std;

class Folder: public Node {
    friend class FolderIterator;

public:
    Folder(string path): _path(path) {
        size_t found = path.find_last_of('/');
        if(found == string::npos || _path.back() == '/') {
            throw invalid_argument("path format error");
        }
        _name = path.substr(found+1);

    }

    ~Folder() override {}

    string name() const override {
        return _name;
    }

    string path() const override {
        return _path;
    }

    void add(Node * node) override {
        size_t found = node->path().find_last_of('/');
        if(_path != node->path().substr(0, found)) {
            throw invalid_argument("node and folder are in the different directory");
        }
        _nodes.push_back(node);
        node->setParent(this);
    }

    FolderIterator * createIterator() override {
        return new FolderIterator(this);
    }

    Node * getChildByName(const char * name) const override {
        Node * node = nullptr;
        for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
            Node * n = *it;
            if (n->name() == name) {
                node = n;
                return node;
            }
        }
        return node;
    }

    Node * find(string path) override {
        Node * node = nullptr;
        auto it = this->createIterator();
        for (it->first(); !it->isDone(); it->next()) {
            Node * n = it->currentItem();
            if (n->path() == path) {
                node = n;
                return node;
            }
            Folder * f = dynamic_cast<Folder *>(n);
            if (f) {
                node = f->find(path);
            }
            if (node) {
                return node;
            }
        }
        delete it;
        return node;
    }

    int numberOfFiles() const override {
        int count = 0;
        for (auto it = _nodes.begin(); it != _nodes.end(); it++) {
            Folder * f = dynamic_cast<Folder *>(*it);
            if (f) {
                count += f->numberOfFiles();
            } else {
                count++;
            }
        }
        return count;
    }

    void remove(string path) override {
        Node * node = this->find(path);
        if (node) {
            Folder * parentNode = dynamic_cast<Folder *>(node->getParent());
            parentNode->_remove(node);
            node->setParent();
        }
    }

    void _remove(Node * node) {
        _nodes.remove(node);
    }

private:
    string _path;
    string _name;
    list<Node *> _nodes;
};


#endif // FOLDER
