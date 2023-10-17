#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

#include "iterator.h"

class Node;

class NullIterator : public Iterator {
public:
    NullIterator() {}
    
    void first() override {
        return;
    }
    bool isDone() const override {
        return true;
    }
    Node * currentItem() const override {
        return nullptr;
    }
    void next() {
        return;
    };
};

#endif // NULL_ITERATOR_H
