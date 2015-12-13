#include "inventory.h"

Inventory::Inventory()
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = 0;
    }
}

Inventory::Inventory(Inventory const & inventory)
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = inventory.resources[i];
    }
}

Inventory& Inventory::operator=(Inventory const & inventory)
{
    for (size_t i = 0; i < NUM_RESOURCES; i++)
    {
        resources[i] = inventory.resources[i];
    }
}

Resource const Inventory::operator[](ResourceType type) const
{
    return resources[type];
}

Resource const Inventory::get_resource(ResourceType type) const
{
    return resources[type];
}

void Inventory::set_resource(ResourceType type, Resource amount)
{
    if (amount < 0)
        amount = 0;
    if (amount > capacity[type])
        amount = capacity[type];
    resources[type] = amount;
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
