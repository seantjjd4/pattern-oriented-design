#include <gtest/gtest.h>
#include "../src/link.h"
#include "../src/file.h"

TEST(Link, link_of_file) {
    File * file = new File("structure/file.txt");
    Link * link = new Link("structure/link", file);
    ASSERT_EQ("link", link->name());
    ASSERT_EQ("structure/file.txt", link->getTarget()->path());
}