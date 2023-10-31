# <engine name :D>

### About
<engine name :D> is a 2D game engine that is rendered using vulkan with glfw for the window
Looking to add opengl support once vulkan rendering is working

### Usage
Games are split into scenes, where each scene is defined by the objects it creates and renders. Only once scene can be active at a time.
```
class MainMenu : public core::Scene
{
  void Tick(float delta) override{
  }
  void onEnter() override{
  }
  void onExit() override{
  }
}
```
Each scene must override the Tick method (which is called every game update), the onEnter method (which is called before the scene begins) and onExit (which is called when the scene is swapped out)

In order to get the engine to render your scene, simply initialise the engine, and start it with a new instance of your scene
```
int main()
{
  core::Engine e;
  if(e.Init())
    return -1;
  e.Run(new MainMenu());
}
```
Note that the engine::Init method must always be called first. If it returns anything other than 0 then the engine could not be initialised.

In addition, if you want to change engine settings such as the ```tickrate``` or ```name``` then you can get the engine settings using
```
int main()
{
  ...
  core::engine_settings_t* settings = e.GetEngineSettings();
  settings->tickrate = 120; // default 60
  ...
}
```
