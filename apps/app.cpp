#include "..\include\engine\engine.hpp"
#include "..\include\engine\scene.hpp"
#include "..\include\engine\manager.hpp"
#include "..\include\engine\entity.hpp"

#include <iostream>


class MainMenu : public core::Scene
{
public:
    void Tick(float delta) override {
    }
    void OnEnter() override {
        std::cout << "Entering scene\n";
    }
    void OnExit() override {
        std::cout << "Exiting scene\n";
    }
};


class Player : public ent::Sprite2D
{
public:
    void Tick()
    {
        // Player update code here
        transform.x +=1;
        transform.scale = 1.5;

    }
}



int main()
{
    core::Engine a;
    core::engine_settings_t* settings = a.GetEngineSettings();
    settings->tickrate = 70;

    std::cout << a.GetEngineSettings()->tickrate;

    if(a.Init())
        return -1;

    ent::Entity* entity = new Entity(1.2);

    core::GameTimer* timer = (core::GameTimer*)core::SystemManager::GetManager()->GetSystem(SYS_TIMER);

    a.Run(new MainMenu());
}
