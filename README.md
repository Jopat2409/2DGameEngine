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
