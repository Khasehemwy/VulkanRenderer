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
		VkPhysicalDevice physicalDevice
	);

	static std::vector<char> readFile(const std::string& filename);

	static VkShaderModule createShaderModule(const std::vector<char>& code, const VkDevice& device);
};