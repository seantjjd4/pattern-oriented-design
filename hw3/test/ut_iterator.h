#include "../src/node.h"
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"
#include "../src/order_by.h"

class IteratorTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        home = new Folder("structure/home");

        profile = new File("structure/home/my_profile");
        home->add(profile);

        document = new Folder("structure/home/Documents");
        home->add(document);

        favorite = new Folder("structure/home/Documents/favorites");
        document->add(favorite);
        ddd = new File("structure/home/Documents/favorites/domain-driven-design.pdf");
        favorite->add(ddd);
        ca = new File("structure/home/Documents/favorites/clean-architecture.pdf");
        favorite->add(ca);
        cqrs = new File("structure/home/Documents/favorites/cqrs.pdf");
        favorite->add(cqrs);

        note = new File("structure/home/Documents/note.txt");
        document->add(note);

        download = new Folder("structure/home/Downloads");
        home->add(download);

        funny = new File("structure/home/Downloads/funny.png");
        download->add(funny);

        visitor_folder = new Folder("structure/visitor");
        file1 = new File("structure/visitor/file1.txt");
        visitor_folder->add(file1);
        file2 = new File("structure/visitor/file2.txt");
        visitor_folder->add(file2);
        nested = new Folder("structure/visitor/nested");
        visitor_folder->add(nested);
        file3 = new File("structure/visitor/nested/file3.txt");
        nested->add(file3);
        file4 = new File("structure/visitor/nested/file4.txt");
        nested->add(file4);
    }

    void TearDown() {
        delete home;
        delete profile;
        delete download;
        delete document;
        delete note;
        delete favorite;
        delete ddd;
        delete ca;
        delete cqrs;
        delete funny;

        delete visitor_folder;
        delete file1;
        delete file2;
        delete nested;
        delete file3;
        delete file4;
    }
    
    Node * home;
    Node * profile;
    Node * download;
    Node * document;
    Node * note;
    Node * favorite;
    Node * ddd;
    Node * ca;
    Node * cqrs;
    Node * funny;

    Node * visitor_folder;
    Node * file1;
    Node * file2;
    Node * nested;
    Node * file3;
    Node * file4;
};

TEST_F(IteratorTest, Normal) {
    Iterator * it = home->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("my_profile", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("Documents", it->currentItem()->name());

    it->next();
    ASSERT_EQ("Downloads", it->currentItem()->name());

    it->next();
    ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, NotAvaliableIterator) {
    Iterator * it = home->createIterator();
    it->first();
    ASSERT_FALSE(it->isDone());
    
    ASSERT_EQ("my_profile", it->currentItem()->name());
    
    it->next();
    ASSERT_EQ("Documents", it->currentItem()->name());
    
    home->add(new File("structure/home/hello.txt"));
    ASSERT_ANY_THROW(it->next());
    ASSERT_ANY_THROW(it->first());
    ASSERT_EQ("Documents", it->currentItem()->name());
    ASSERT_FALSE(it->isDone());
}

TEST_F(IteratorTest, DFS) {
    Iterator * dfsIt = new DfsIterator(home);

    dfsIt->first();
    ASSERT_EQ("my_profile", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Documents", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("favorites", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("domain-driven-design.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("clean-architecture.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("cqrs.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("note.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Downloads", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("funny.png", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_TRUE(dfsIt->isDone());
}


TEST_F(IteratorTest, BFS) {
    Iterator * bfsIt = new BfsIterator(home);

    bfsIt->first();
    ASSERT_EQ("my_profile", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("Documents", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("Downloads", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("favorites", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("note.txt", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("funny.png", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("domain-driven-design.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("clean-architecture.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_EQ("cqrs.pdf", bfsIt->currentItem()->name());

    bfsIt->next();
    ASSERT_TRUE(bfsIt->isDone());
}

TEST_F(IteratorTest, OrderByNameIterator) {
    Iterator * obnIt = home->createIterator(OrderBy::Name);

    obnIt->first();
    ASSERT_EQ("Documents", obnIt->currentItem()->name());

    obnIt->next();
    ASSERT_EQ("Downloads", obnIt->currentItem()->name());

    obnIt->next();
    ASSERT_EQ("my_profile", obnIt->currentItem()->name());

    obnIt->next();
    ASSERT_TRUE(obnIt->isDone());
}

TEST_F(IteratorTest, OrderByNameWithFolderFirstIterator) {
    Iterator * obnwffIt = visitor_folder->createIterator(OrderBy::NameWithFolderFirst);

    obnwffIt->first();
    ASSERT_EQ("nested", obnwffIt->currentItem()->name());

    obnwffIt->next();
    ASSERT_EQ("file1.txt", obnwffIt->currentItem()->name());

    obnwffIt->next();
    ASSERT_EQ("file2.txt", obnwffIt->currentItem()->name());

    obnwffIt->next();
    ASSERT_TRUE(obnwffIt->isDone());
}

TEST_F(IteratorTest, OrderByKindIterator) {
    Iterator * obkIt = home->createIterator(OrderBy::Kind);

    obkIt->first();
    ASSERT_EQ("my_profile", obkIt->currentItem()->name());

    obkIt->next();
    ASSERT_EQ("Documents", obkIt->currentItem()->name());

    obkIt->next();
    ASSERT_EQ("Downloads", obkIt->currentItem()->name());

    obkIt->next();
    ASSERT_TRUE(obkIt->isDone());
}