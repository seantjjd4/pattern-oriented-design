#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;

PainterMapper::PainterMapper() {

}

Painter * PainterMapper::find(std::string id) {
    return static_cast<Painter *>(abstractFind(id, PainterMapper::callback));
}

void PainterMapper::add(DomainObject * painter) {
    abstractAdd(painter);
}

void PainterMapper::update(std::string id) {
    abstractUpdate(getDomainObject(id));
}

void PainterMapper::del(std::string id) {
    abstractDelete(id);
}

std::string PainterMapper::updateStmt(DomainObject * domainObject) const {
    std::string stmt = "";
    Painter* painter = dynamic_cast<Painter*>(domainObject);
    if (painter != nullptr) {
        stmt = "UPDATE painter SET Name='" + painter->name() + "' WHERE ID='" + painter->id() + "'";
    }
    return stmt;
}

std::string PainterMapper::findByIdStmt(std::string id) const {
    std::string stmt = "SELECT * FROM painter WHERE ID='" + id + "'";
    return stmt;
}

std::string PainterMapper::addStmt(DomainObject * domainObject) const {
    std::string stmt = "";
    Painter* painter = dynamic_cast<Painter*>(domainObject);
    if (painter != nullptr) {
        stmt = "INSERT INTO painter VALUES ('" + painter->id() + "', '" + painter->name() +"')";
    }
    return stmt;
}

std::string PainterMapper::deleteByIdStmt(std::string id) const
{
    std::string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}

PainterMapper *PainterMapper::instance() {
    if (_instance == nullptr)
    {
        _instance = new PainterMapper();
    }
    return _instance;
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = new Painter(argv[0], argv[1], false);
    PainterMapper::instance()->load(painter);
    return 0;
}