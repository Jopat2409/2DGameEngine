#ifndef _INTERNAL_SCENE_H
#define _INTERNAL_SCENE_H

#include "EngineExport.hpp"


namespace core{
    class ENGINE_API Scene{
    public:
        virtual void OnEnter() = 0;
        virtual void Tick(float delta) = 0;
        virtual void OnExit() = 0;
    };
}


#endif
