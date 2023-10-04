#ifndef _INTERNAL_ENGINE_H
#define _INTERNAL_ENGINE_H


#include "EngineExport.hpp"

#include "logger.hpp"
#include "scenemanager.hpp"
#include "gametimer.hpp"

#include "scene.hpp"
#include "manager.hpp"

namespace core{

    struct ENGINE_API engine_settings_t{
        float tickrate{60.0};
        char* name{"Application"};
    };

    class ENGINE_API Engine{
    public:
        Engine();
        ~Engine();

        [[nodiscard]] int Init();
        void Run(Scene* mainScene);

        engine_settings_t* GetEngineSettings();
        void SetEngineSettings(engine_settings_t& settings);


    private:

        [[nodiscard]] int InitLibs();
        [[nodiscard]] int InitVideo();
        [[nodiscard]] int InitAudio();
        [[nodiscard]] int InitEngine();

        void Tick(float delta);
        void Draw();
        void HandleInput();
        void Exit();

        engine_settings_t m_Settings;

        // Systems
        SystemManager* m_SysMgrInstance;

        bool m_IsRunning{false};

        float m_UpdatesPerSecond{0};
        float m_FramesPerSecond{0};


    };
}





#endif
