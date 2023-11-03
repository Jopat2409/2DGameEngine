#ifndef _INTERNAL_MANAGER_H
#define _INTERNAL_MANAGER_H

#include "EngineExport.hpp"
#include "gametimer.hpp"
#include "console.hpp"

#include <memory>
#include <unordered_map>
#include <string>


namespace core
{

    class SystemManager
    {
    public:
        SystemManager();
        ~SystemManager();

        ENGINE_API static System* GetSystem(const char* identifier);

        ENGINE_API void RegisterSystem(System* system, const char* identifier);

        ENGINE_API static SystemManager* GetManager();

        int Init();
        void Exit();

        void Tick();
        void Render(void* graphics);

    private:

        int InitSystems();

        static SystemManager* m_Instance;
        bool m_IsInit{false};

        std::unordered_map<std::string, System*> m_ActiveSystems;

    };
}

#define GET_SYSTEM(sys, tp) ((tp*)core::SystemManager::GetManager()->GetSystem(sys))


#endif
