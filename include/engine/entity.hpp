#ifndef _INTERNAL_ENTITY_H
#define _INTERNAL_ENTITY_H

#include "component.hpp"

namespace ent
{
    class Entity
    {
    public:
        template<typename T, typename... Args>
        inline Entity(T t, Args... args)
        {

        }
        ~Entity();

    };
}

#endif
