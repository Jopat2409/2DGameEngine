#ifndef _INTERNAL_CONSOLE_H
#define _INTERNAL_CONSOLE_H

#include "convar.hpp"
#include <map>
#include <string>
#include "logger.hpp"

namespace core{

    class Console : public core::System
    {
    public:
        
        int Init() override;
        void Exit() override;
        void Tick() override;

        void RegisterConvar(ConVar* cvar);
        ConVar* FindConvar(const char* name);

    private:
        std::map<std::string, ConVar*> m_ConVars;
    };
}

inline int core::Console::Init()
{
    return 0;
}
inline void core::Console::Exit()
{
}
inline void core::Console::Tick()
{

}

inline void core::Console::RegisterConvar(ConVar* cvar)
{
    m_ConVars[cvar->GetName()] = cvar;
}

inline core::ConVar* core::Console::FindConvar(const char* name)
{
    return m_ConVars.count(name) ? m_ConVars.at(name) : nullptr;
}

#define SYS_CONSOLE "Console001"

#endif
