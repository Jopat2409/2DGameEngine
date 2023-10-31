#ifndef _INTERNAL_ECS_H
#define _INTERNAL_ECS_H

#include "system.hpp"

namespace ent
{

    class Entity;

    class ECS : public core::System
    {
    friend class Entity;
    public:
        int Init() override;
        void Exit() override;
        void Tick() override;

        ENGINE_API void* CreateComponent(int componentType);

        void* GetComponent(Entity* ent, int component);
    };
}

#define SYS_ECS "EntityComponentSystem001"

#endif
