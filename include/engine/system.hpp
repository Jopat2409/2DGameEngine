#ifndef _INTERNAL_SYSTEM_H
#define _INTERNAL_SYSTEM_H

#include "EngineExport.hpp"


namespace core
{
    class ENGINE_API System{
    public:
        [[nodiscard]] virtual int Init() = 0;

        virtual void Tick() = 0;
        virtual void Render(void* graphics){};

        virtual void Exit() = 0;
    private:
        const char* m_Identifier;
    };
}

#endif
