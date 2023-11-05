#pragma once 

#include <list>
#include <unordered_map>
#include <sys/stat.h>
#include <iostream>
#include "node.h"
#include "iterator.h"
#include "order_by.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    // Iterator * createIterator() override {
    //     return new FolderIterator(this, _operationCount);
    // }

    Iterator * createIterator(OrderBy orderBy = OrderBy::Normal) override {
        switch (orderBy) {
            case OrderBy::Normal:
                return new FolderIterator(this, _operationCount);
            case OrderBy::Name:
                return new OrderByNameIterator(this, _operationCount);
            case OrderBy::NameWithFolderFirst:
                return new OrderByNameWithFolderFirstIterator(this, _operationCount);
            case OrderBy::Kind:
                return new OrderByKindIterator(this, _operationCount);
            default:
                return new FolderIterator(this, _operationCount);
        }
    }

    Node * find(string path) override {
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

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator: public Iterator {
    public:
        OrderByNameIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~OrderByNameIterator() {}

        void first() {
            checkAvailable();
            _order = _host->_nodes;
            _order.sort(compareName);
            _current = _order.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _order.end();
        }
    private:
        Folder* const _host;
        std::list<Node *> _order;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        static bool compareName(Node* a, Node* b) {
            return a->name() < b->name();
        }
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
    public:
        OrderByNameWithFolderFirstIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~OrderByNameWithFolderFirstIterator() {}

        void first() {
            checkAvailable();
            splitFolder();
            _orderNonFolder.sort(compareName);
            _order.sort(compareName);
            _order.splice(_order.end(), _orderNonFolder);
            _current = _order.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _order.end();
        }
    private:
        Folder* const _host;
        std::list<Node *> _orderNonFolder;
        std::list<Node *> _order;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        void splitFolder() {
            for (auto it = _host->_nodes.begin(); it != _host->_nodes.end(); it++) {
                if (dynamic_cast<Folder *>(*it)) {
                    _order.push_back(*it);
                } else {
                    _orderNonFolder.push_back(*it);
                }
            }
        }

        static bool compareName(Node* a, Node* b) {
            return a->name() < b->name();
        }
    };

    class OrderByKindIterator: public Iterator {
    public:
        OrderByKindIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~OrderByKindIterator() {}

        void first() {
            checkAvailable();
            splitAllKind();
            sortAllKind();
            _current = _order.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _order.end();
        }
    private:
        Folder* const _host;
        std::list<Node *> _order;
        std::list<std::string> _orderKey;
        std::map<std::string, std::list<Node *>> _allKind;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }

        void splitAllKind() {
            for (auto it = _host->_nodes.begin(); it != _host->_nodes.end(); it++) {
                if (dynamic_cast<Folder *>(*it)) {
                    if (_allKind.count("folder") == 0) {
                        _orderKey.push_back("folder");
                    }
                    _allKind["folder"].push_back(*it);
                } else {
                    size_t pos = (*it)->name().find_last_of('.');
                    if (pos == std::string::npos) {
                        if (_allKind.count("file") == 0) {
                            _orderKey.push_back("file");
                        }
                        _allKind["file"].push_back(*it);
                    } else {
                        std::string type = (*it)->name().substr(pos+1);
                        if (_allKind.count(type) == 0) {
                            _orderKey.push_back(type);
                        }
                        _allKind[type].push_back(*it);
                    }
                }
            }
        }

        void sortAllKind() {
            for (auto it = _allKind.begin(); it != _allKind.end(); it++) {
                it->second.sort(compareName);
                _order.splice(_order.end(), it->second);
            }
        }

        static bool compareName(Node* a, Node* b) {
            return a->name() < b->name();
        }
    };
};
