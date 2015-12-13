#pragma once

#include <iostream>
#include "resource.h"

class Inventory {
    Resource resources[NUM_RESOURCES];
    Resource capacity[NUM_RESOURCES];
public:
    Inventory();

    Inventory(Inventory const &);

    Inventory& operator=(Inventory const &);

    Resource const operator[](ResourceType) const;

    Resource const get_resource(ResourceType) const;

    void set_resource(ResourceType, Resource);

    bool operator==(Inventory const &) const;
};
