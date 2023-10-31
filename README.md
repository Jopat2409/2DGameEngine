# <engine name :D>

### About
<engine name :D> is a 2D game engine that is rendered using vulkan with glfw for the window
Looking to add opengl support once vulkan rendering is working

### Usage - Getting Started
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

### Usage - Interacting With the Engine Systems
There are many different systems provided by the engine such as a console, entity-component system and game timer.
In order to interact with these systems, aquire them via the GET_SYSTEM macro
```
GET_SYSTEM(SYS_CONSOLE, core::Console) // returns the console system
GET_SYSTEM(SYS_TIMER, core::GameTimer) // returns the game timer
```
In order to see all the relevant systems, their types, locations and usage, read the documentation duh

### Usage - Console Variables
In order to keep track of variables that may be changed during runtime by the user, or for variables that must be used over mutliple files / systems, console variables can be used, and they are initialised as such
```
core::ConVar("m_testCVar", "0.1");
core::ConVar("m_boundedCVar", "0.1", true, 0, true, 10); // bounded between 0 and 10
```

You can then access the console variable by aquiring the console system and calling FindCvar()
```
core::ConVar* test = GET_SYSTEM(SYS_CONSOLE, core::Console)->FindConvar("m_testCVar");
test->GetFloat(); // -> 0.1
test->GetString(); // -> "0.1"
test->GetInt(); // undefined :0
test->SetValue("7.5");
```
