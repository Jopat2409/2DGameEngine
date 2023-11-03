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

    /***
     * A base entiy that contains a transform, sprite 
    */
    class Sprite2D : public Entity
    {
    public:
        Sprite2D(float x, float y, const char* texture, int flags=0);
        ~Sprite2D();
    };

    class DynamicSprite2D : public Entity
    {
    public:
        DynamicSprite2D(float x, float y, const char** texture, int flags=0);
        ~DynamicSprite2D();
    };
}

#endif
