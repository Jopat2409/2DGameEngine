#include "..\include\engine\scenemanager.hpp"

int core::SceneManager::Init()
{
    return 0;
}
void core::SceneManager::Exit()
{
    ClearScene();
}
void core::SceneManager::Tick()
{
    m_CurrentScene->Tick(0.);
}
void core::SceneManager::Render(void* graphics)
{

}
void core::SceneManager::SetScene(core::Scene* scene)
{
    // Deal with old scene
    ClearScene();

    // Set new scene
    m_CurrentScene = scene;
    m_CurrentScene->OnEnter();
}

void core::SceneManager::ClearScene()
{
    if(m_CurrentScene){
        m_CurrentScene->OnExit();
        delete m_CurrentScene;
    }
}
