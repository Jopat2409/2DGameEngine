#ifndef _INTERNAL_ENTITY_H
#define _INTERNAL_ENTITY_H

#include "component.hpp"

namespace ent
{
    class Entity
    {
    public:
        Entity(int compFlags = 0);
        ~Entity();

        void AddComponent(int compFlags);
    };
}

#endif
