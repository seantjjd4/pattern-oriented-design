#include <stdexcept>

#include "../src/file.h"
#include "../src/iterator.h"

TEST(FileTest, FileInit) {
    ASSERT_NO_THROW(File file("/folder1/file1.txt"));
}

TEST(FileTest, FileInitWithWrongPath) {
    ASSERT_THROW(File file("/folder1/file1.txt/"), std::invalid_argument);
}

TEST(FileTest, FileInitWithWrongSytax) {
        
    ASSERT_THROW(File file("\\folder1\\file1.txt"), std::invalid_argument);
}

TEST(FileTest, getName) {
    File file("/folder1/file1.txt");
    ASSERT_EQ("file1.txt", file.name());
}

TEST(FileTest, getPath) {
    File file("/folder1/file1.txt");
    ASSERT_EQ("/folder1/file1.txt", file.path());
}

TEST(FileTest, createIterator) {
    File * n1 = new File("/folder1/file1.txt");
    Iterator * it = n1->createIterator();
    it->first();
    ASSERT_TRUE(it->isDone());
    
    delete n1;
    delete it;
}