#pragma once 

#include <string>
#include "../src/folder.h"

using namespace std;

TEST(Folder, normal) {
    Folder root("./src/root");

    ASSERT_EQ("root", root.name());
    ASSERT_EQ("./src/root", root.path());
}

TEST(Folder, add_file) {
    Folder root("./src/root");
    File file0_1("./src/root/file0_1.txt");
    root.add(&file0_1);

    ASSERT_EQ("file0_1.txt", root.getChildByName("file0_1.txt")->name());
}

TEST(Folder, add_incorrect_path_file_to_folder) {
    Folder root("./src/root");
    File file1_1("./src/root/folder1_1/file1_1.txt");
    ASSERT_ANY_THROW(root.add(&file1_1));
}

TEST(Folder, add_folder) {
    Folder root("./src/root");
    Folder folder1_1("./src/root/folder1_1");

    root.add(&folder1_1);

    ASSERT_EQ("folder1_1", root.getChildByName("folder1_1")->name());
}