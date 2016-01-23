#include "inventory.h"

using std::ostream;
using std::endl;

Inventory::Inventory()
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = 0;
        capacity[i] = BASE_CAPACITY;
    }
}

Inventory::Inventory(Inventory const & inventory)
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = inventory.resources[i];
        capacity[i] = inventory.capacity[i];
    }
}

Inventory& Inventory::operator=(Inventory const & inventory)
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = inventory.resources[i];
        capacity[i] = inventory.capacity[i];
    }
    return * this;
}

Resource const Inventory::operator[](ResourceType type) const
{
    return resources[type];
}

Resource const Inventory::get_resource(ResourceType type) const
{
    return resources[type];
}

Resource const Inventory::get_capacity(ResourceType type) const
{
    return capacity[type];
}

void Inventory::set_resource(ResourceType type, Resource amount)
{
    if (amount < 0)
        amount = 0;
    if (amount > capacity[type])
        amount = capacity[type];
    resources[type] = amount;
}

void Inventory::set_capacity(ResourceType type, Resource amount)
{
    capacity[type] = amount;
}

void Inventory::print_resource(ostream & os, ResourceType type) const
{
    os << resources[type] << "/" << capacity[type];
}

bool Inventory::operator==(Inventory const & inventory) const
{
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        if (resources[i] != inventory.resources[i])
            return false;
    }

    return true;
}

ostream& operator<<(ostream & os, Inventory const & inventory)
{
    os << " Gold: "; inventory.print_resource(os, GOLD); os << endl;
    os << " Jems: "; inventory.print_resource(os, JEMS); os << endl;
    os << " Food: "; inventory.print_resource(os, FOOD); os << endl;
    os << "Water: "; inventory.print_resource(os, WATER); os << endl;
    os << "Cloth: "; inventory.print_resource(os, CLOTH);

    return os;
}
