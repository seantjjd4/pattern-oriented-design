#pragma once

#include <string>
#include <stack>
#include <iostream>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {}

    Folder * getRoot() const {
        return _builder->getRoot();
    }

    void parse() {
        FileSystemScanner * _scanner = new FileSystemScanner();
        _scanner->setPath(_currentPath);
        _scanner->nextNode();
        while(!_scanner->isDone()) {
            string name = _scanner->currentNodeName();
            if (_scanner->isFolder()) {
                string temp = _currentPath;
                _currentPath = _currentPath + "/" + name;
                _builder->buildFolder(_currentPath);
                parse();
                _currentPath = temp;
            } else if (_scanner->isFile()) {
                _builder->buildFile(_currentPath + "/" + name);
            }
            _scanner->nextNode();
        }
        _builder->endFolder();
    }

    void setPath(string path) {
        _path = path;
        _currentPath = _path;
        _builder->setRoot(_path);
    }
    

private:
    string _path;
    string _currentPath;
    FileSystemBuilder * _builder;
};
