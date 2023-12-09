#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class DomainObject;
class Drawing;
class Scanner;
class Parser;
class Builder;

class DrawingMapper : public AbstractMapper
{
public:
    Drawing *find(std::string id);

    // add
    void add(DomainObject *drawing);

    // update
    void update(std::string id);

    // delete
    void del(std::string id);

    std::string updateStmt(DomainObject *domainObject) const;

    std::string findByIdStmt(std::string id) const;

    std::string addStmt(DomainObject *domainObject) const;

    std::string deleteByIdStmt(std::string id) const;

    static DrawingMapper *instance();

protected:
    DrawingMapper();

    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::list<Shape *> convertShapes(int argc, char **argv);

private:
    static DrawingMapper *_instance;
    Builder *_builder;
    Scanner *_scanner;
    Parser *_parser;
};