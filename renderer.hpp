#ifndef _INTERNAL_RENDERER_H
#define _INTERNAL_RENDERER_H

/***
 * This file is for all things related to rendering within the engine
 *
*/



#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW\glfw3native.h>

#include <unordered_map>
#include "logger.hpp"
#include "EngineExport.hpp"

namespace gfx
{
    class GPU;
    typedef bool(__thiscall *gpu_callback_t)(GPU*);

    class GPU
    {
    public:
        GPU();
        GPU(VkPhysicalDevice* device, gpu_callback_t suitability_funct=nullptr);
        ~GPU();

        void Populate(VkPhysicalDevice* device, gpu_callback_t suitability=nullptr);
        void Init(VkSurfaceKHR windowSurface);
        void Cleanup();
        inline VkPhysicalDevice* GetDevice() { return m_Device; };
        inline VkQueueFamilyProperties* GetQueue(int queue){ return &m_Queues[m_QueueMap[queue]];};


        bool CheckSuitable();

        ENGINE_API inline bool IsSuitable() { return m_IsSuitable; };
        ENGINE_API inline const char* GetName() { return m_Props.deviceName; };

        ENGINE_API VkDevice GetLogicalDevice();
    private:
        void FindQueues(VkSurfaceKHR windowSurface);


    private:

        void SetupLogicalDevice();

        VkPhysicalDevice* m_Device{nullptr};
        VkDevice m_LogicalDevice{nullptr};

        uint32_t m_QueueCount{0};
        VkQueueFamilyProperties* m_Queues{nullptr};
        std::unordered_map<uint32_t, uint32_t> m_QueueMap;

        VkPhysicalDeviceProperties m_Props;
        VkPhysicalDeviceFeatures m_Feats;

        bool m_IsSuitable{false};
    }; // namespace gfx

    class Renderer
    /*
    This class is not exposed as an interface as it is passed to all Draw(gfx::Renderer* gfx);
    */
    {
    public:
        Renderer();
        ~Renderer();

        int Init(int width=640, int height=480);
        void Exit();

        ENGINE_API inline GLFWwindow* GetWindow() {return m_EngineWindow; };
        ENGINE_API GPU GetGPU(int index);
        ENGINE_API inline void SetGPU(int index);

    private:

        // Initialisation functions
        void InitGLFW();
        void InitWindowSurface();
        // Vulkan stuff
        void InitVulkan();
        void CreateVulkanInstance();
        void FindPhysicalDevices();
        void SetupSurface();

        void CleanupGLFW();
        void CleanupVulkan();

        bool m_IsInit{false};

        GLFWwindow* m_EngineWindow{nullptr};

#ifndef ENGINE_OPENGL_RENDERER
        VkInstance m_VulkanInstance;

        // Physical device properties
        uint32_t m_NumPhysDevices{0};
        VkPhysicalDevice* m_PhysDevices{nullptr};
        GPU* m_AvailableGPUs{nullptr};
        GPU* m_CurrentGPU{nullptr};

        VkSurfaceKHR m_WindowSurface;

#endif
        int m_Width{0}, m_Height{0}; // Will be convars later but just variables for now


    }; // namespace gfx
}

#endif
