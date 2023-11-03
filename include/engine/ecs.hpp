#ifndef _INTERNAL_ECS_H
#define _INTERNAL_ECS_H

#include "component.hpp"
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

        ENGINE_API int CreateEntity(int componentFlags);

        ENGINE_API int GetNextEntity();
        ENGINE_API int GetMaxEntityIndex();
        
        COMPONENT(c_info)
        COMPONENT(c_transform)
        COMPONENT(c_light)
        COMPONENT(c_physics)
        COMPONENT(c_render)
    private:
        int m_entityPtr{0};
    };
}

#define SYS_ECS "EntityComponentSystem001"

#endif
