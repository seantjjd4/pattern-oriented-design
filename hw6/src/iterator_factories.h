#pragma once

#include "iterator_factory.h"
#include "iterator.h"
#include "folder.h"

class FolderIteratorFactory: public IteratorFactory {
public:
    static FolderIteratorFactory * instance() {
        return new FolderIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::FolderIterator(node, operationCount);
    }
};

class OrderByNameIteratorFactory: public IteratorFactory {
public:
    static OrderByNameIteratorFactory * instance() {
        return new OrderByNameIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameIterator(node, operationCount);
    }
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    static OrderByNameWithFolderFirstIteratorFactory * instance() {
        return new OrderByNameWithFolderFirstIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }
};

class OrderByKindIteratorFactory: public IteratorFactory {
public:
    static OrderByKindIteratorFactory * instance() {
        return new OrderByKindIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByKindIterator(node, operationCount);
    }
};
