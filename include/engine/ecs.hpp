#ifndef _INTERNAL_ECS_H
#define _INTERNAL_ECS_H

#include "system.hpp"

namespace ent
{
    class ECS : public core::System
    {
    public:
        int Init() override;
        void Exit() override;
        void Tick() override;

        ENGINE_API void* CreateComponent(int componentType);
    private:

    };
}

#define SYS_ECS "EntityComponentSystem001"

#endif
