#ifndef _INTERNAL_SCENEMANAGER_H
#define _INTERNAL_SCENEMANAGER_H

#include "EngineExport.hpp"
#include "scene.hpp"
#include "system.hpp"

namespace core
{
    class SceneManager : public System
    {
    public:

        int Init() override;
        void Exit() override;
        void Tick() override;
        void Render(void* graphics) override;

        ENGINE_API void SetScene(Scene* scene);

    private:
        Scene* m_CurrentScene{nullptr};

        void ClearScene();

    };
}


#define SYS_SCENEMANAGER "SCENEMANAGER001"

#endif
