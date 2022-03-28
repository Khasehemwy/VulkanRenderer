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

    std::vector<VkDescriptorSet> descriptorSets;
    VkDescriptorSetLayout descriptorSetLayout;
    void createDescriptorPool() override;
    void createDescriptorSetLayout() override;
    void createDescriptorSets() override;

    virtual void createPipeline() override;

    std::vector<VkCommandBuffer> commandBuffers;
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

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

    uint32_t currentFrame = 0;
    void drawFrame();
};