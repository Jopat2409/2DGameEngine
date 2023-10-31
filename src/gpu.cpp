#include <engine/renderer.hpp>


#define FIND_QUEUE(f) if(m_Queues[i].queueFlags & f){\
                        m_QueueMap[f] = i;\
};

gfx::GPU::GPU()
{

}

gfx::GPU::GPU(VkPhysicalDevice* device, gpu_callback_t callback)
{
    Populate(device, callback);
}

void gfx::GPU::Init(VkSurfaceKHR windowSurface)
{
    FindQueues(windowSurface);
    SetupLogicalDevice();
}

void gfx::GPU::Cleanup()
{
    delete[] m_Queues;
    vkDestroyDevice(m_LogicalDevice, nullptr);
}

void gfx::GPU::FindQueues(VkSurfaceKHR windowSurface)
{
    LOG_INFO("Finding GPU Queues for logical device")
    vkGetPhysicalDeviceQueueFamilyProperties(*m_Device, &m_QueueCount, nullptr);
    m_Queues = new VkQueueFamilyProperties[m_QueueCount];
    vkGetPhysicalDeviceQueueFamilyProperties(*m_Device, &m_QueueCount, m_Queues);

    std::cout << windowSurface;
    for(int i=0; i < m_QueueCount; i++){
        FIND_QUEUE(VK_QUEUE_GRAPHICS_BIT);

        VkBool32 present{false};
        vkGetPhysicalDeviceSurfaceSupportKHR(*m_Device, i, windowSurface, &present);
    }
}

VkDevice gfx::GPU::GetLogicalDevice()
{
    if(!m_LogicalDevice)
        SetupLogicalDevice();
    return m_LogicalDevice;
}

void gfx::GPU::SetupLogicalDevice()
{
    LOG_INFO("Setting up logical device for selected GPU")
    VkDeviceQueueCreateInfo info;
    info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.queueFamilyIndex = m_QueueMap[VK_QUEUE_GRAPHICS_BIT];
    info.queueCount = 1;

    float priority{1.0f};
    info.pQueuePriorities = &priority;

    VkPhysicalDeviceFeatures features{};

    VkDeviceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &info;
    createInfo.enabledLayerCount = 0;
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledExtensionCount = 0;
    createInfo.ppEnabledExtensionNames = nullptr;
    createInfo.pEnabledFeatures = &features;

    ASSERT((vkCreateDevice(*m_Device, &createInfo, nullptr, &m_LogicalDevice) == VK_SUCCESS),
        "Could not create logical device unfortunately....");

}

void gfx::GPU::Populate(VkPhysicalDevice* device, gpu_callback_t callback)
{
    LOG_INFO("Populating GPU")
    m_Device = device;

    vkGetPhysicalDeviceProperties(*m_Device, &m_Props);
    vkGetPhysicalDeviceFeatures(*m_Device, &m_Feats);

    // Get suitability 
    m_IsSuitable = CheckSuitable() && callback ? callback(this) : 1;

    LOG_INFO("GPU populated")
}

gfx::GPU::~GPU()
{

}

bool gfx::GPU::CheckSuitable()
{
    /**
     * Engine defined suitability check
    */
    return true;
}

