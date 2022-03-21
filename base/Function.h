/*
* base Function.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "VulkanBase.h"

std::vector<char> readFile(const std::string& filename);

uint32_t findMemoryType(
	VkPhysicalDevice& physicalDevice,
	uint32_t typeFilter,
	VkMemoryPropertyFlags properties
);

VkFormat findSupportedFormat(
	const std::vector<VkFormat>& candidates,
	VkImageTiling tiling,
	VkFormatFeatureFlags features, 
	VkPhysicalDevice physicalDevice
);

void createImage(
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

const std::string getAssetPath();
