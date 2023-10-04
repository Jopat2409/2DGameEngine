
#include "..\include\engine\logger.hpp"
#include "..\include\engine\manager.hpp"
#include "..\include\engine\scenemanager.hpp"
#include "..\include\engine\ecs.hpp"

core::SystemManager* core::SystemManager::m_Instance = nullptr;

core::SystemManager::SystemManager()
{
    // Register internal engine systems
    LOG_INFO("Creating systems")
    RegisterSystem(new GameTimer(), SYS_TIMER);
    RegisterSystem(new SceneManager(), SYS_SCENEMANAGER);
    RegisterSystem(new ent::ECS(), SYS_ECS);
}
core::SystemManager::~SystemManager()
{
    Exit();
}

core::System* core::SystemManager::GetSystem(const char* identifier)
{
    return GetManager()->m_ActiveSystems.at(identifier);
}

void core::SystemManager::RegisterSystem(System* system, const char* identifier)
{
    // Ensure no memory leakage for retarded devs
    if(m_ActiveSystems[identifier])
        delete m_ActiveSystems[identifier];

    // Register the system
    m_ActiveSystems[identifier] = system;
}

int core::SystemManager::Init()
{
    if(!m_IsInit){
        LOG_INFO("Initialising Systems")
        m_IsInit = true;
        InitSystems();
        return 0;
    }
    return -1;
}

void core::SystemManager::Exit()
{
    // Clear up systems
    for(auto& sys: m_ActiveSystems){
        sys.second->Exit();
        delete sys.second;
    }
}

void core::SystemManager::Tick()
{
    for(auto& sys: m_ActiveSystems)
        sys.second->Tick();
}

void core::SystemManager::Render(void* graphics)
{
    for(auto& sys: m_ActiveSystems)
        sys.second->Render(graphics);
}

int core::SystemManager::InitSystems()
{
    int r_code = 0;
    for(auto& sys: m_ActiveSystems){
        r_code += sys.second->Init();
    }

    return r_code;
}

core::SystemManager* core::SystemManager::GetManager()
{
    if(!m_Instance)
        m_Instance = new SystemManager();
    return m_Instance;
}
