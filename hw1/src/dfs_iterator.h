#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include <stack>
#include <queue>

#include "iterator.h"
#include "node.h"

// class Iterator;

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite): _composite(composite) {}

    ~DfsIterator() {}

    void first() {
        _it = _composite->createIterator();
        _it->first();
    }

    Node * currentItem() const {
        return _it->currentItem();
    }

    void next() {
        Iterator * tempIt = _it->currentItem()->createIterator();
        tempIt->first();
        _it->next();
        // check is there are any subNode
        if (!tempIt->isDone()) {
            // check if there are any Node left in the same level
            if (!_it->isDone()) {
                _stack.push(_it);
            }
            _it = tempIt;
            _it->first();

        } else {
            if (_it->isDone() && !_stack.empty()) {
                _it = _stack.top();
                _stack.pop();
            }
        }
    }
    
    bool isDone() const {
        bool isSubNodeDone = true;
        if (!_it->isDone()) {
            Iterator * tempIt = _it->currentItem()->createIterator();
            tempIt->first();
            isSubNodeDone = tempIt->isDone();
        }
        return _stack.empty() && isSubNodeDone && _it->isDone();
    }

private:
    Node * _composite;
    Iterator * _it;
    std::stack<Iterator *> _stack;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite): _composite(composite) {}

    ~BfsIterator() {}

    void first() {
        _it = _composite->createIterator();
        _it->first();
    }

    Node * currentItem() const {
        return _it->currentItem();
    }

    void next() {
        Iterator * tempIt = _it->currentItem()->createIterator();
        tempIt->first();
        _it->next();
        // check if there are any Node left in the same level
        if (!_it->isDone()) {
            // check if there are any subNode
            if (!tempIt->isDone()) {
                _queue.push(tempIt);
            }
        } else {
            if (!tempIt->isDone()) {
                _queue.push(tempIt);
            }
            if (!_queue.empty()) {
                _it = _queue.front();
                _queue.pop();
                _it->first();
            }
        }
    }
    
    bool isDone() const {
        bool isSubNodeDone = true;
        if (!_it->isDone()) {
            Iterator * tempIt = _it->currentItem()->createIterator();
            tempIt->first();
            isSubNodeDone = tempIt->isDone();
        }
        return _queue.empty() && isSubNodeDone && _it->isDone();
    }

private:
    Node * _composite;
    Iterator * _it;
    std::queue<Iterator *> _queue;
};

#endif // DFS_ITERATOR_H
