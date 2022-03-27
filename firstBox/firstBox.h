/*
* firstBox firstBox.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "VulkanBase.h"

class firstBox: public VulkanBase {
public:
    void run();

    virtual ~firstBox();
private:

    const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    glm::mat4 model, view, proj;

    void initVulkan();
    void mainLoop();
    void cleanup();

    virtual bool isDeviceSuitable(VkPhysicalDevice device);
    virtual VkSurfaceFormatKHR chooseSwapSurfaceFormat(
        const std::vector<VkSurfaceFormatKHR>& availableFormats);
    virtual VkPresentModeKHR chooseSwapPresentMode(
        const std::vector<VkPresentModeKHR>& availablePresentModes);
    virtual VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    void recreateSwapChain();
    void cleanupSwapChain();

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    void createDescriptorPool();
    void createDescriptorSets();

    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    virtual void createPipeline();

    std::vector<VkCommandBuffer> commandBuffers;
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    void createSyncObjects();

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();

    void updateUniformBuffer(uint32_t currentImage);

    Texture2D* texture;
    void createTexture();

    virtual void createDepthResources();
    bool hasStencilComponent(VkFormat format);

    uint32_t currentFrame = 0;
    void drawFrame();
};