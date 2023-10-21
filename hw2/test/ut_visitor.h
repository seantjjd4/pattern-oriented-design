#pragma once 

#include <iostream>
#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/visitor.h"
#include "../src/find_by_name_visitor.h"
#include "../src/stream_out_visitor.h"

class VisitorTest: public ::testing::Test {
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

TEST_F(VisitorTest, find_by_name_visitor) {
    Node * folder1_1_2 = new Folder("./src/root/folder1_1/folder1_1");
    folder1_1->add(folder1_1_2);
    FindByNameVisitor * fv = new FindByNameVisitor("folder1_1");
    root->accept(fv);

    ASSERT_EQ("./src/root/folder1_1", fv->getPaths().front());
    ASSERT_EQ("./src/root/folder1_1/folder1_1", fv->getPaths().back());
    ASSERT_EQ(2, fv->getPaths().size());
}

TEST_F(VisitorTest, stream_out_visitor_visit_folder) {
    StreamOutVisitor * sv = new StreamOutVisitor();
    root->accept(sv);
    std::string standard =R"(_____________________________________________
./src/root/file0_1.txt
---------------------------------------------
Hi, I'm file0_1.txt
Hello world...

Goodbye!
_____________________________________________

_____________________________________________
./src/root/folder1_1/file1_1.txt
---------------------------------------------
Hi, I'm file1_1.txt
Hello world...

Goodbye!
_____________________________________________

_____________________________________________
./src/root/folder1_2/file1_2.txt
---------------------------------------------
Hi, I'm file1_2.txt
Hello world...

Goodbye!
_____________________________________________

_____________________________________________
./src/root/folder1_2/folder2_2/file2_2.txt
---------------------------------------------
Hi, I'm file2_2.txt
Hello world...

Goodbye!
_____________________________________________

_____________________________________________
./src/root/folder1_2/folder2_2/file2_3.txt
---------------------------------------------
Hi, I'm file2_3.txt
Hello world...

Goodbye!
_____________________________________________

)";
    ASSERT_EQ(standard, sv->getResult());
}

TEST_F(VisitorTest, stream_out_visitor_visit_file) {
    StreamOutVisitor * sv = new StreamOutVisitor();
    file0_1->accept(sv);
    std::string standard =R"(_____________________________________________
./src/root/file0_1.txt
---------------------------------------------
Hi, I'm file0_1.txt
Hello world...

Goodbye!
_____________________________________________
)";
    ASSERT_EQ(standard, sv->getResult());
}