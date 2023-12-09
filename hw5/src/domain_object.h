#pragma once

#include <string>
#include "unit_of_work.h"

class DomainObject {
public:
    DomainObject(std::string id, bool isNew=true): _id(id) {
        if (isNew) {
            UnitOfWork::instance()->registerNew(this);
        }
    }

    std::string id() const {
        return _id;
    }

    virtual ~DomainObject() {

    }
    
protected:
    std::string _id;
};