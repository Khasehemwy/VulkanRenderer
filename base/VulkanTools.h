/*
* base VulkanTools.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include <bits/stdc++.h>
#include "vulkan/vulkan.h"

class VulkanTools
{
public:
	static VkFormat findSupportedFormat(
		const std::vector<VkFormat>& candidates,
		VkImageTiling tiling,
		VkFormatFeatureFlags features,
		VkPhysicalDevice& physicalDevice
	);

	static std::vector<char> readFile(const std::string& filename);

	static VkShaderModule createShaderModule(const std::vector<char>& code, const VkDevice& device);

	static void createBuffer(
		VkDeviceSize size, 
		VkBufferUsageFlags usage, 
		VkMemoryPropertyFlags properties, 
		VkBuffer& buffer, 
		VkDeviceMemory& bufferMemory,
		VkDevice& device,
		VkPhysicalDevice& physicalDevice
	);

	static void createImage(
		uint32_t width, 
		uint32_t height, 
		VkFormat format, 
		VkImageTiling tiling, 
		VkImageUsageFlags usage, 
		VkMemoryPropertyFlags properties, 
		VkImage& image, 
		VkDeviceMemory& imageMemory, 
		VkDevice& device, 
		VkPhysicalDevice& physicalDevice
	);

	static uint32_t findMemoryType(
		VkPhysicalDevice& physicalDevice,
		uint32_t typeFilter,
		VkMemoryPropertyFlags properties
	);

	static void transitionImageLayout(
		VkImage& image,
		VkFormat format,
		VkImageLayout oldLayout,
		VkImageLayout newLayout,
		VkCommandPool& commandPool,
		VkQueue& queue,
		VkDevice& device
	);

	static VkCommandBuffer beginSingleTimeCommands(VkDevice& device, VkCommandPool& commandPool);
	static void endSingleTimeCommands(
		VkDevice& device, 
		VkCommandPool& commandPool, 
		VkCommandBuffer& commandBuffer,
		VkQueue& queue
	);

	static void copyBufferToImage(
		VkBuffer& buffer,
		VkImage& image,
		uint32_t width,
		uint32_t height,
		VkCommandPool& commandPool,
		VkQueue& queue,
		VkDevice& device
	);

	static void copyBuffer(
		VkBuffer& srcBuffer,
		VkBuffer& dstBuffer,
		VkDeviceSize size,
		VkDevice& device,
		VkCommandPool& commandPool,
		VkQueue& queue
	);
};