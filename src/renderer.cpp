#include <engine/renderer.hpp>
#include <stdexcept>
#include <iostream>

bool __thiscall IsValid(gfx::GPU* self){

    return true;
}

gfx::Renderer::Renderer()
{

}
gfx::Renderer::~Renderer()
{
    if(m_IsInit)
        Exit();
}

int gfx::Renderer::Init(int width, int height)
{
    m_IsInit = true;
    m_Width = width;
    m_Height = height;
    InitGLFW();
#ifndef ENGINE_OPENGL_RENDERER
    InitVulkan();
    InitWindowSurface();
    FindPhysicalDevices();
#else
    InitOpenGL();
#endif
    return 0;
}

void gfx::Renderer::Exit()
{
#ifndef ENGINE_OPENGL_RENDERER
    CleanupVulkan();
#else
    CleanupOpenGL();
#endif
    CleanupGLFW();
}


void gfx::Renderer::InitGLFW()
{
    LOG_INFO("Initialising GLFW");
    /***
     * Initialise the glfw components of the renderer
     * Creates the window and applies flags
     * TODO: add ability to customise window flags
    */

    ASSERT(glfwInit(), "Could not initialise glfw");

#ifndef ENGINE_OPENGL_RENDERER
    // We are rendering with vulkan so do not use OPENGL glfw
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_EngineWindow = glfwCreateWindow(m_Width, m_Height, "Engine Window", nullptr, nullptr);
    ASSERT(m_EngineWindow, "Window could not be created!")
}
void gfx::Renderer::InitVulkan()
{
    CreateVulkanInstance();
}

void gfx::Renderer::InitWindowSurface()
{
    glfwCreateWindowSurface(m_VulkanInstance, m_EngineWindow, nullptr, &m_WindowSurface);
    ASSERT(m_WindowSurface, "Window surface could not be created");
}

void gfx::Renderer::CreateVulkanInstance()
{
    /***
     * Creates an instance of the vulkan rendering api
     * Adds app info.
     * TODO: Replace app name with user defined app name
    */

    // Create the app info struct
    VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "placeholder name";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Create the createInfo struct
    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = NULL;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;


    // Get the glfw extensions for vulkan rendering
    uint32_t extCount;
    const char** extensions = glfwGetRequiredInstanceExtensions(&extCount);

    createInfo.enabledExtensionCount = extCount;
    createInfo.ppEnabledExtensionNames = extensions;

    // Create instance
    ASSERT((vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance) == VK_SUCCESS), 
        "Could not create vulkan instance. You suck :P");
    

}

void gfx::Renderer::FindPhysicalDevices()
{
    LOG_INFO("Finding Physical Devices");
    vkEnumeratePhysicalDevices(m_VulkanInstance, &m_NumPhysDevices, nullptr);

    ASSERT(m_NumPhysDevices, "Could not find any GPUs");

    m_PhysDevices = new VkPhysicalDevice[m_NumPhysDevices];
    m_AvailableGPUs = new GPU[m_NumPhysDevices];

    vkEnumeratePhysicalDevices(m_VulkanInstance, &m_NumPhysDevices, m_PhysDevices);

    for(int i = 0; i < m_NumPhysDevices; i++){
        m_AvailableGPUs[i].Populate(&m_PhysDevices[i]);
    };

    SetGPU(0);


}

void gfx::Renderer::SetGPU(int index)
{
    LOG_INFO("Setting GPU to new GPU")
    ASSERT((index < m_NumPhysDevices), "GPU specified could not be found in system!");
    if(m_CurrentGPU)
        m_CurrentGPU->Cleanup();
    m_CurrentGPU = &m_AvailableGPUs[index];
    m_CurrentGPU->Init(m_WindowSurface);
}

void gfx::Renderer::SetupSurface()
{
    VkWin32SurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.hinstance = GetModuleHandle(nullptr);
    createInfo.hwnd = glfwGetWin32Window(m_EngineWindow);

    ASSERT((glfwCreateWindowSurface(m_VulkanInstance, m_EngineWindow, nullptr, &m_WindowSurface) == VK_SUCCESS),
        "Could not create window surface...");
}

void gfx::Renderer::CleanupGLFW()
{
    glfwDestroyWindow(m_EngineWindow);
    glfwTerminate();
}

void gfx::Renderer::CleanupVulkan()
{
    delete[] m_PhysDevices;
    delete[] m_AvailableGPUs;
    vkDestroySurfaceKHR(m_VulkanInstance, m_WindowSurface, nullptr);
    vkDestroyInstance(m_VulkanInstance, nullptr);
}