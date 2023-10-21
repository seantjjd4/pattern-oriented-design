#pragma once 

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"

class NodeTest: public ::testing::Test {
protected:
    void SetUp() {
        root = new Folder("./src/root");

        file0_1 = new File("./src/root/file0_1.txt");
        root->add(file0_1);

        folder1_1 = new Folder("./src/root/folder1_1");
        root->add(folder1_1);

        folder1_2 = new Folder("./src/root/folder1_2");
        root->add(folder1_2);

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
        delete file1_2;
        delete folder2_2;
        delete file2_2;
        delete file2_3;
    }
    
    Node * root;
    Node * file0_1;
    Node * folder1_1;
    Node * folder1_2;
    Node * file1_2;
    Node * folder2_2;
    Node * file2_2;
    Node * file2_3;
};


TEST_F(NodeTest, numberOfFiles) {
    ASSERT_EQ(4, root->numberOfFiles());
}

TEST_F(NodeTest, find_a_file) {
    Node * result = root->find("./src/root/folder1_2/folder2_2/file2_3.txt");
    ASSERT_EQ(file2_3, result);
}

TEST_F(NodeTest, find_a_file_not_exist) {
    Node * result = root->find("./src/root/folder1_2/folder2_2/file2_4.txt");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, find_a_folder) {
    Node * result = folder1_2->find("./src/root/folder1_2/folder2_2");
    ASSERT_EQ(folder2_2, result);
}

TEST_F(NodeTest, find_a_folder_not_exist) {
    Node * result = folder1_2->find("./src/root/folder1_2/folder2_3");
    ASSERT_EQ(nullptr, result);
}

TEST_F(NodeTest, delete_a_file) {
    ASSERT_EQ(file2_3->name(), root->find("./src/root/folder1_2/folder2_2/file2_3.txt")->name());
    root->remove("./src/root/folder1_2/folder2_2/file2_3.txt");
    ASSERT_EQ(nullptr, root->find("./src/root/folder1_2/folder2_2/file2_3.txt"));
}

TEST_F(NodeTest, delete_a_folder) {
    ASSERT_EQ(folder2_2->name(), root->find("./src/root/folder1_2/folder2_2")->name());
    root->remove("./src/root/folder1_2/folder2_2");
    ASSERT_EQ(nullptr, root->find("./src/root/folder1_2/folder2_2"));
}
