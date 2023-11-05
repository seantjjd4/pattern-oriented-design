#include "../src/file_system_parser.h"
#include "../src/file_system_builder.h"
#include "../src/file_system_scanner.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

TEST(ParserTest, parser) {
    FileSystemParser * parser = new FileSystemParser(new FileSystemBuilder());
    parser->setPath("structure/home");
    parser->parse();
    Folder * root = parser->getRoot();
    ASSERT_EQ("structure/home", root->path());


    Iterator * obnIt = root->createIterator(OrderBy::Name);

    obnIt->first();
    ASSERT_EQ("Documents", obnIt->currentItem()->name());
    obnIt->next();
    ASSERT_EQ("Downloads", obnIt->currentItem()->name());
    obnIt->next();
    ASSERT_EQ("hello.txt", obnIt->currentItem()->name());
    obnIt->next();
    ASSERT_EQ("my_profile", obnIt->currentItem()->name());
    obnIt->next();
    ASSERT_TRUE(obnIt->isDone());

    Iterator * obnIt1 = root->getChildByName("Documents")->createIterator(OrderBy::Name);
    obnIt1->first();
    ASSERT_EQ("favorites", obnIt1->currentItem()->name());
    obnIt1->next();
    ASSERT_EQ("hello.txt", obnIt1->currentItem()->name());
    obnIt1->next();
    ASSERT_EQ("note.txt", obnIt1->currentItem()->name());
    obnIt1->next();
    ASSERT_EQ("programming", obnIt1->currentItem()->name());
    obnIt1->next();
    ASSERT_TRUE(obnIt1->isDone());

    Iterator * obnIt2 = root->getChildByName("Downloads")->createIterator(OrderBy::Name);
    obnIt2->first();
    ASSERT_EQ("funny.png", obnIt2->currentItem()->name());
    obnIt2->next();
    ASSERT_TRUE(obnIt2->isDone());

    Iterator * obnIt3 = root->getChildByName("Documents")->getChildByName("favorites")->createIterator(OrderBy::Name);
    obnIt3->first();
    ASSERT_EQ("clean-architecture.pdf", obnIt3->currentItem()->name());
    obnIt3->next();
    ASSERT_EQ("cqrs.pdf", obnIt3->currentItem()->name());
    obnIt3->next();
    ASSERT_EQ("domain-driven-design.pdf", obnIt3->currentItem()->name());
    obnIt3->next();
    ASSERT_TRUE(obnIt3->isDone());



}