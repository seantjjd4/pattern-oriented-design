#pragma once

#include "node.h"
#include "visitor.h"

class Link: public Node {
public:
    Link(std::string path, Node * target): Node(path), _target(target) {

    }

    int numberOfFiles() const override {
        return _target->numberOfFiles();
    }

    Node * find(string path) override {
        return _target->find(path);
    }

    std::list<string> findByName(string name) override {
        return _target->findByName(name);
    }

    void add(Node * node) override {
        return _target->add(node);
    }

    void remove(string path) override {
        return _target->remove(path);
    }

    Node * getChildByName(const char * name) const override {
        return _target->getChildByName(name);
    }

    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

    void renameHook(std::string path) override {
        updatePath(path);
        _target->renameHook(path);
    }

    Node * getTarget() const {
        return _target;
    }

private:
    Node * _target;
};