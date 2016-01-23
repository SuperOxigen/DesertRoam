#pragma once

#include <iostream>
#include "resource.h"

#define BASE_CAPACITY 10

class Inventory {
    Resource resources[NUM_RESOURCES];
    Resource capacity[NUM_RESOURCES];
public:
    Inventory();

    Inventory(Inventory const &);

    Inventory& operator=(Inventory const &);

    Resource const operator[](ResourceType) const;

    Resource const get_resource(ResourceType) const;
    Resource const get_capacity(ResourceType) const;

    void set_resource(ResourceType, Resource);
    void set_capacity(ResourceType, Resource);

    void print_resource(std::ostream&, ResourceType) const;

    bool operator==(Inventory const &) const;

    friend std::ostream& operator<<(std::ostream&, Inventory const &);
};
