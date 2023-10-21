#pragma once 

#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

class IteratorTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        root = new Folder("./src/root");

        file0_1 = new File("./src/root/file0_1.txt");
        root->add(file0_1);

        folder1_1 = new Folder("./src/root/folder1_1");
        root->add(folder1_1);

        folder1_2 = new Folder("./src/root/folder1_2");
        root->add(folder1_2);

        file1_1 = new File("./src/root/folder1_1/file1_1.txt");
        folder1_1->add(file1_1);

        file1_2 = new File("./src/root/folder1_2/file1_2.txt");
        folder1_2->add(file1_2);

        folder2_2 = new Folder("./src/root/folder1_2/folder2_2");
        folder1_2->add(folder2_2);
        file2_2 = new File("./src/root/folder1_2/folder2_2/file2_2.txt");
        folder2_2->add(file2_2);
        file2_3 = new File("./src/root/folder1_2/folder2_2/file2_3.txt");
        folder2_2->add(file2_3);
    }

    void TearDown() {
        delete root;
        delete file0_1;
        delete folder1_1;
        delete folder1_2;
        delete file1_1;
        delete file1_2;
        delete folder2_2;
        delete file2_2;
        delete file2_3;
    }
    
    Node * root;
    Node * file0_1;
    Node * folder1_1;
    Node * folder1_2;
    Node * file1_1;
    Node * file1_2;
    Node * folder2_2;
    Node * file2_2;
    Node * file2_3;
};

TEST_F(IteratorTest, Normal) {
    Iterator * it = root->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("file0_1.txt", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("folder1_1", it->currentItem()->name());

    it->next();
    ASSERT_EQ("folder1_2", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, DFS) {
    Iterator * dfsIt = new DfsIterator(root);

    dfsIt->first();
    ASSERT_EQ("file0_1.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("folder1_1", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file1_1.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("folder1_2", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file1_2.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("folder2_2", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file2_2.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("file2_3.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}


TEST_F(IteratorTest, BFS) {
    Iterator * bfsIt = new BfsIterator(root);

    bfsIt->first();
    ASSERT_EQ("file0_1.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("folder1_1", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("folder1_2", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file1_1.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file1_2.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("folder2_2", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file2_2.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("file2_3.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST_F(IteratorTest, throw_if_structure_changed) {
    Iterator * it = root->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    Node * file0_2 = new File("./src/root/file0_2.txt");
    root->add(file0_2);
    ASSERT_ANY_THROW(it->next());
    ASSERT_ANY_THROW(it->first());
}
