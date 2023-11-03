#ifndef _INTERNAL_COMPONENT_H
#define _INTERNAL_COMPONENT_H

#define CMP_TRANSFORM (1<<0)
#define CMP_SPRITE (1<<2)
#define CMP_PHYS (1<<3)
#define CMP_LIGHT (1<<4)

#define MAX_ENTITIES 1000
#define COMPONENT(t)private:\
                        t m_##t[MAX_ENTITIES];
#define GET_COMPONENT(ent, t) m_##t[ent]

namespace ent
{
    struct c_info
    {
        uint32_t flags;
    };
    struct c_transform
    {
        float x{0}, y{0};
        float scale_x{0}, scale_y{0};
        float rot_x{0}, rot_y{0};
    };
    struct c_render
    {
        const char* id{nullptr};
    };
    
    typedef enum{
        MODEL_PARTICLE = 0,
        MODEL_PLANE = 1,
    } phys_model_t;

    struct c_physics
    {
        float weight{0};
        float vel_x{0}, vel_y{0};
        float accel_x{0}, accel_y{0};
        phys_model_t model_type{MODEL_PARTICLE};
    };
    struct c_light
    {
        float intensity{0.5};
        const char* hex{"FFFFFF"};
    };
}

#endif
