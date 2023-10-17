#include <string>

#include "../src/folder.h"
#include "../src/iterator.h"

TEST(FolderTest, FolderInit) {
    ASSERT_NO_THROW(File file("/folder1/folder2"));
}

TEST(FolderTest, FolderInitWithWrongPath) {
    ASSERT_THROW(File file("/folder1/folder2/"), std::invalid_argument);
}

TEST(FolderTest, FolderInitWithWrongSytax) {
    ASSERT_THROW(File file("\\folder1\\folder2"), std::invalid_argument);
}

TEST(FolderTest, getName) {
    Folder folder("/folder1/folder2/folder3");
    ASSERT_EQ("folder3", folder.name());
}

TEST(FolderTest, getPath) {
    Folder folder("/folder1/folder2/folder3");
    ASSERT_EQ("/folder1/folder2/folder3", folder.path());
}

TEST(FolderTest, addNode) {
    Folder folder1("/folder1/folder2");
    Folder folder2("/folder1/folder2/folder3");

    Node * n1 = &folder1;
    Node * n2 = &folder2;
    ASSERT_THROW(folder2.add(n1), std::invalid_argument);
    folder1.add(n2);
    ASSERT_EQ(n1, n2->getParent());
}

TEST(FolderTest, createIterator) {
    Folder * n1 = new Folder("/folder1/folder2");
    File * n2 = new File("/folder1/folder2/file3");
    n1->add(n2);
    Iterator * it = n1->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());

    delete n1;
    delete n2;
    delete it;
}

TEST(FolderTest, createIteratorInEmptyFolder) {
    Folder * n1 = new Folder("/folder1/folder2");
    Iterator * it = n1->createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());

    delete n1;
    delete it;
}

TEST(FolderTest, iteratorFunction) {
    Folder * n1 = new Folder("/folder1/folder2");
    Folder * n2 = new Folder("/folder1/folder2/folder3");
    Folder * n3 = new Folder("/folder1/folder2/folder4");
    n1->add(n2);
    n1->add(n3);

    Iterator * it = n1->createIterator();

    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder3", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder4", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete n1;
    delete n2;
    delete it;
}

TEST(FolderTest, findNode) {
    Folder * f1 = new Folder("/folder1/folder2");
    Folder * f2 = new Folder("/folder1/folder2/folder3");
    Folder * f3 = new Folder("/folder1/folder2/folder4");
    File * fi1 = new File("/folder1/folder2/folder3/file1.txt");
    Folder * fi2 = new Folder("/folder1/folder2/folder4/folder5");
    File * fi3 = new File("/folder1/folder2/folder4/file2.txt");
    f2->add(fi1);
    f3->add(fi2);
    f3->add(fi3);
    f1->add(f2);
    f1->add(f3);
    
    Node * n = f1->find("/folder1/folder2/folder4/file2.txt");
    ASSERT_EQ("/folder1/folder2/folder4/file2.txt", n->path());
    n = f1->find("/folder1/folder2/folder4/folder6");
    ASSERT_EQ(nullptr, n);
    n = f1->find("/folder1/folder2/folder4");
    ASSERT_EQ("/folder1/folder2/folder4", n->path());

    delete f1;
    delete f2;
    delete f3;
    delete fi1;
    delete fi2;
    delete fi3;
}

TEST(FolderTest, getNumberOfFiles) {
    Folder * f1 = new Folder("/folder1/folder2");
    Folder * f2 = new Folder("/folder1/folder2/folder3");
    Folder * f3 = new Folder("/folder1/folder2/folder4");
    File * fi1 = new File("/folder1/folder2/folder3/file1.txt");
    Folder * fi2 = new Folder("/folder1/folder2/folder4/folder5");
    File * fi3 = new File("/folder1/folder2/folder4/file2.txt");
    f2->add(fi1);
    f3->add(fi2);
    f3->add(fi3);
    f1->add(f2);
    f1->add(f3);

    ASSERT_EQ(2, f1->numberOfFiles());
}

TEST(FolderTest, removeNode) {
    Folder * f1 = new Folder("/folder1/folder2");
    Folder * f2 = new Folder("/folder1/folder2/folder3");
    Folder * f3 = new Folder("/folder1/folder2/folder4");
    File * fi1 = new File("/folder1/folder2/folder3/file1.txt");
    Folder * fi2 = new Folder("/folder1/folder2/folder4/folder5");
    File * fi3 = new File("/folder1/folder2/folder4/file2.txt");
    f2->add(fi1);
    f3->add(fi2);
    f3->add(fi3);
    f1->add(f2);
    f1->add(f3);
    ASSERT_EQ("/folder1/folder2/folder4/file2.txt", f1->find("/folder1/folder2/folder4/file2.txt")->path());
    f1->remove("/folder1/folder2/folder4/file2.txt");
    ASSERT_EQ(nullptr, f1->find("/folder1/folder2/folder4/file2.txt"));
    ASSERT_EQ("/folder1/folder2/folder4/folder5", f1->find("/folder1/folder2/folder4/folder5")->path());

    f1->remove("/folder1/folder2/folder3");
    ASSERT_EQ(nullptr, f1->find("/folder1/folder2/folder3/file1.txt"));
    ASSERT_EQ(nullptr, f1->find("/folder1/folder2/folder3"));

    delete f1;
    delete f2;
    delete f3;
    delete fi1;
    delete fi2;
    delete fi3;
}

TEST(FolderTest, getChildByName) {
    Folder * f1 = new Folder("/folder1/folder2");
    Folder * f2 = new Folder("/folder1/folder2/folder3");
    Folder * f3 = new Folder("/folder1/folder2/folder4");

    f1->add(f2);
    f1->add(f3);

    Node * n = f1->getChildByName("folder3");
    ASSERT_EQ("/folder1/folder2/folder3", n->path());
    n = f1->getChildByName("folder6");
    ASSERT_EQ(nullptr, n);
    n = f1->getChildByName("folder4");
    ASSERT_EQ("/folder1/folder2/folder4", n->path());

    delete f1;
    delete f2;
    delete f3;
}