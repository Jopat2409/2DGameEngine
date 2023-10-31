#ifndef _INTERNAL_COMPONENT_H
#define _INTERNAL_COMPONENT_H

#define CMP_TRANSFORM (1<<0)
#define CMP_SPRITE (1<<2)
#define CMP_PHYS (1<<3)
#define CMP_LIGHT (1<<4)

namespace ent
{
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
    struct c_physics
    {
        float weight{0};
    };
    struct c_light
    {
        float intensity{0.5};
        const char* hex{"FFFFFF"};
    };
}

#endif
