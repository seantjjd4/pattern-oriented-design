#include "../src/file_system_builder.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/dfs_iterator.h"

TEST(BuilderTest, builder)  {
    FileSystemBuilder * builder = new FileSystemBuilder();
    builder->setRoot("structure/home");
    builder->buildFile("structure/home/hello.txt");
    builder->buildFolder("structure/home/Documents");
    builder->buildFolder("structure/home/Documents/favorites");
    builder->buildFile("structure/home/Documents/favorites/clean-architecture.pdf");
    builder->buildFile("structure/home/Documents/favorites/cqrs.pdf");
    builder->endFolder();
    builder->endFolder();
    builder->buildFolder("structure/home/Downloads");
    builder->buildFile("structure/home/Downloads/funny.png");
    builder->endFolder();
    builder->buildFile("structure/home/my_profile");

    Folder * root = builder->getRoot();
    Iterator * dfsIt = new DfsIterator(root);

    dfsIt->first();
    ASSERT_EQ("hello.txt", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Documents", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("favorites", dfsIt->currentItem()->name());
    dfsIt->next();
    ASSERT_EQ("clean-architecture.pdf", dfsIt->currentItem()->name());
    dfsIt->next();
    ASSERT_EQ("cqrs.pdf", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("Downloads", dfsIt->currentItem()->name());
    dfsIt->next();
    ASSERT_EQ("funny.png", dfsIt->currentItem()->name());

    dfsIt->next();
    ASSERT_EQ("my_profile", dfsIt->currentItem()->name());

}