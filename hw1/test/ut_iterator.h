#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/folder.h"

TEST(IteratorTest, FolderIterator) {
    Folder * f1 = new Folder("/folder1/folder2");
    Folder * f2 = new Folder("/folder1/folder2/folder3");
    Folder * f3 = new Folder("/folder1/folder2/folder4");
    f1->add(f2);
    f1->add(f3);
    FolderIterator * it = new FolderIterator(f1);
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder3", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder4", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete f1;
    delete f2;
    delete f3;
    delete it;
}

TEST(IteratorTest, DfsIterator) {
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
    DfsIterator * it = new DfsIterator(f1);
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder3", it->currentItem()->name());
    
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("file1.txt", it->currentItem()->name());

    ASSERT_TRUE(it->currentItem()->createIterator()->isDone());
    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder4", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder5", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("file2.txt", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete f1;
    delete f2;
    delete f3;
    delete fi1;
    delete fi2;
    delete fi3;
    delete it;
}

TEST(IteratorTest, BfsIterator) {
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
    BfsIterator * it = new BfsIterator(f1);
    it->first();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder3", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder4", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("file1.txt", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("folder5", it->currentItem()->name());

    it->next();
    ASSERT_FALSE(it->isDone());
    ASSERT_EQ("file2.txt", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());

    delete f1;
    delete f2;
    delete f3;
    delete fi1;
    delete fi2;
    delete fi3;
    delete it;
}
