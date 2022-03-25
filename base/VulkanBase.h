/*
* base VulkanBase.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bits/stdc++.h>
#include <array>
#include <chrono>
#include <stdexcept>
#include <cstdlib>
#include <optional>

#include "stb_image.h"

struct UniformBufferObject;

class Window;
class Camera;
class Input;
class VulkanTools;

#include "Types.h"
#include "Function.h"
#include "Window.h"
#include "Camera.h"
#include "Input.h"
#include "VulkanTools.h"

class VulkanBase
{
public:
	struct Settings {
		/** @brief Activates validation layers (and message output) when set to true */
		bool validation = false;
	} settings;

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete();
	};
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};


	VulkanBase();
	virtual ~VulkanBase();

	virtual void setName(const std::string name);
	virtual const std::string getAssetPath() const;
	virtual void createInstance();
	virtual void createRenderPass();
	virtual void createDescriptorSetLayout();
	virtual void createPipeline() = 0;
	virtual void initVulkan();
	virtual bool isDeviceSuitable(const VkPhysicalDevice& device);
	virtual VkPhysicalDeviceFeatures createDeviceFeatures();
	virtual VkFormat findDepthFormat();
	virtual VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	virtual VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	virtual VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	virtual VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	

protected:
	Window* window;
	Camera* camera;
	Input* inputs;

	std::string name = "Vulkan Base";

	VkInstance instance;
	VkSurfaceKHR surface;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	VkRenderPass renderPass;

	VkDescriptorSetLayout descriptorSetLayout;


	std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
	std::vector<const char*>* pValidationLayers = &validationLayers;

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	const std::vector<const char*>* pDeviceExtensions = &deviceExtensions;

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void destroyDebugUtilsMessengerEXT(
		VkInstance instance, 
		VkDebugUtilsMessengerEXT debugMessenger, 
		const VkAllocationCallbacks* pAllocator
	);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	virtual void createSwapChain();
	void createImageViews();//todo: should be private.
private:
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();

	void setupDebugMessenger();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	);
	VkResult createDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger
	);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};