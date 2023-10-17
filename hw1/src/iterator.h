#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include <list>

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    ~FolderIterator();
    void first();
    bool isDone() const;
    Node * currentItem() const;
    void next();


private:
    Folder * _composite;
    std::list<Node *>::iterator _it;
};


#endif // ITERATOR_H
