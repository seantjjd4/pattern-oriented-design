#pragma once 

#include "../src/file.h"

TEST(File, normal) {
    File file0_1("./src/root/file0_1.txt");
    ASSERT_EQ("file0_1.txt", file0_1.name());
    ASSERT_EQ("./src/root/file0_1.txt", file0_1.path());
}

TEST(File, throw_if_wrong_path) {
    ASSERT_ANY_THROW(File file0_1("./src/file0_1.txt"));
}

TEST(File, throw_if_folder_path_given) {
    ASSERT_ANY_THROW(File file0_1("./src/root/folder1"));
}