#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file) {
        _ss << "_____________________________________________" << std::endl;
        _ss << file->path() << std::endl;
        _ss << "---------------------------------------------" << std::endl;
        readFileContent(file->path());
        _ss << "_____________________________________________" << std::endl;
        if (!_fileOnly) {
            _ss << std::endl;
        }
    }

    void visitFolder(Folder * folder) {
        _fileOnly = false;
        auto it = folder->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    }

    string getResult() const {
        _result = _ss.str();
        return _result;
    }

private:
    bool _fileOnly = true;
    mutable std::string _result;
    std::stringstream _ss;

    void readFileContent(string path) {
        std::ifstream fileStream(path.c_str());
        if (fileStream.is_open()) {
            std::string line;
            while (std::getline(fileStream, line)) {
                _ss << line << std::endl;
            }
            fileStream.close();
        }
    }
};