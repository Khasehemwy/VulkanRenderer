/*
* base Texture.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include <vulkan/vulkan.h>
#include <bits/stdc++.h>
#include "stb_image.h"
#include "VulkanTools.h"

class Texture
{
public:
	VkDevice* device;
	VkImage image;
	VkDeviceMemory memory;
	VkImageLayout layout;
	VkImageView view;
	VkSampler sampler;
};

class Texture2D :public Texture 
{
public:
	Texture2D(VkDevice* device);

	virtual void loadFromFile(
		std::string filePath, 
		int stbFormat, 
		VkPhysicalDevice& physicalDevice,
		VkCommandPool& commandPool,
		VkQueue& queue
	);
};