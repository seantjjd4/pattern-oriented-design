#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>


UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {
    _new.clear();
    _dirty.clear();
    _deleted.clear();
    _clean.clear();
}

UnitOfWork * UnitOfWork::instance() {
    if(_instance == nullptr) {
        _instance = new UnitOfWork();
    }
    return _instance;

}

void UnitOfWork::registerNew(DomainObject * domainObject) {
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject * domainObject) {
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject * domainObject) {
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

void UnitOfWork::registerDeleted(DomainObject * domainObject) {

    if (inClean(domainObject->id()) || inDirty(domainObject->id())) {
        _deleted[domainObject->id()] = domainObject;
    }
    _clean.erase(domainObject->id());
    _new.erase(domainObject->id());
    _dirty.erase(domainObject->id());
}

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {

    for (auto dirty: _dirty) {
        DrawingMapper::instance()->update(dirty.second->id());
        PainterMapper::instance()->update(dirty.second->id());
        registerClean(dirty.second);
    }
    _dirty.clear();

    for (auto newObj: _new) {
        DrawingMapper::instance()->add(newObj.second);
        PainterMapper::instance()->add(newObj.second);
        registerClean(newObj.second);
    }
    _new.clear();

    for (auto deleted: _deleted) {
        DrawingMapper::instance()->del(deleted.second->id());
        PainterMapper::instance()->del(deleted.second->id());
    }
    _deleted.clear();
}