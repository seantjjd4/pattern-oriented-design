#pragma once

#include <string>
#include <dirent.h>

using std::string;

class FileSystemScanner {
public:
    bool isFile() {
        return _file->d_type != DT_DIR;
    }

    bool isFolder() {
        return _file->d_type == DT_DIR;
    }

    bool isDone() {
        return _file == NULL;
    }

    void setPath(string path) {
        _dir = opendir(path.c_str());
    }

    string currentNodeName() {
        string name;
        name.assign(_file->d_name);
        return name;
    }

    void nextNode() {
        do {
            _file = readdir(_dir);
            if (isDone()) {
                break;
            }
        } while (strcmp(_file->d_name, ".") == 0 || strcmp(_file->d_name, "..") == 0);
    }

private:
    DIR * _dir;
    struct dirent * _file;
};
