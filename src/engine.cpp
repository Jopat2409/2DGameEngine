#include "..\include\engine\engine.hpp"

core::Engine::Engine() : m_SysMgrInstance(SystemManager::GetManager())
{
}
core::Engine::~Engine()
{
    Exit();
}

int core::Engine::Init()
{
    return InitEngine();
}
void core::Engine::Run(Scene* mainScene)
{
    m_IsRunning = true;
    ((core::SceneManager*)m_SysMgrInstance->GetSystem(SYS_SCENEMANAGER))->SetScene(mainScene);
    // Game loop

    gametime_t p_time = ((GameTimer*)m_SysMgrInstance->GetSystem(SYS_TIMER))->GetGameTime();
    double lag = 0., timer=0, tps = 1e3/m_Settings.tickrate;
    int frames = 0, updates = 0;

    do{
        // Get elapsed time
        gametime_t c_time = ((GameTimer*)m_SysMgrInstance->GetSystem(SYS_TIMER))->GetGameTime();
        double e_time = c_time - p_time;

        // Increment
        lag += e_time;
        timer += e_time;

        // Update frame counter
        if(timer >= 1000){
            m_FramesPerSecond = frames; frames = 0;
            m_UpdatesPerSecond = updates; updates = 0;
            std::cout << "Running engine with " << m_FramesPerSecond << " frames at a tick rate of " << m_UpdatesPerSecond << " per second.\n";
            timer -= 1000;
        }
        HandleInput();
        // Keep up with the update cycle
        while(lag >= tps){
            Tick(e_time);
            updates += 1;
            lag -= tps;
        }

        // Draw frame
        Draw();
        p_time = c_time;
        frames += 1;

    }while(m_IsRunning && !glfwWindowShouldClose(m_Renderer.GetWindow()));
    Exit();

}

core::engine_settings_t* core::Engine::GetEngineSettings()
{
    return &m_Settings;
}
void core::Engine::SetEngineSettings(engine_settings_t& settings)
{
    m_Settings = settings;
}

int core::Engine::InitLibs()
{
    /**
     * Initialises all 3rd party libraries
    */
    return 0;
}
int core::Engine::InitVideo()
{
    /**
     * Initialises graphics systems
    */
    return 0;
}
int core::Engine::InitAudio()
{
    /**
     * Initialises audio systems
    */
    return 0;
}
int core::Engine::InitEngine()
{
    /**
     * Initialises engine systems
    */
   int return_code = 0;
   LOG_INFO("Initialising Engine")
   return_code += m_Renderer.Init();
   return_code += m_SysMgrInstance->Init();

   return return_code;
}

void core::Engine::Tick(float delta)
{
    m_SysMgrInstance->Tick();
}
void core::Engine::Draw()
{
    m_SysMgrInstance->Render(&m_Renderer);
}
void core::Engine::HandleInput()
{
    glfwPollEvents();
}

void core::Engine::Exit()
{
    m_SysMgrInstance->Exit();
    m_Renderer.Exit();
}
