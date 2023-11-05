#pragma once

#include <vector>
#include <string>
#include "visitor.h"
#include "iterator.h"
#include "order_by.h"

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {}

    void visitFile(File * file) {
    }

    void visitFolder(Folder * folder) {
        _level++;
        Iterator * it = folder->createIterator(_orderBy);
        for(it->first(); !it->isDone();) {
            std::string output = getprefix();

            Node * node = it->currentItem();
            it->next();
            if (it->isDone()) {
                output += "\u2514\u2500\u2500 " + node->name();
            } else {
                output += "\u251c\u2500\u2500 " + node->name();
            }
            setStatus(it->isDone());
            
            _tree += (output + "\n");
            node->accept(this);
        }
        _level--;
    }

    string getTree() {
        return (".\n" + _tree);
    }

private:
    std::string _tree;
    OrderBy _orderBy;
    int _level = -1;
    int _index = 0;
    std::string _isLast;
    std::vector<bool> _status;

    std::string getprefix() {
        std::string prefix;
        for (int i = 0; i < _level; i++) {
            if (_status[i] == false) {
                prefix += "    ";
            } else if (_status[i] == true) {
                prefix += "\u2502   ";
            }
        }
        return prefix;
    }

    void setStatus(bool isDone) {
        if (_level >= int(_status.size())) {
            for (int i = 0; i < _level; i++) {
                if (i > int(_status.size())) {
                    _status.push_back(false);
                }
            }
            _status.push_back(!isDone);
        } else {
            _status[_level] = !isDone;
        }
    }
};