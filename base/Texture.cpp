/*
* base Texture.cpp
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Texture.h"

Texture2D::Texture2D(VkDevice* device)
{
	this->device = device;
}

void Texture2D::loadFromFile(std::string filePath, int stbFormat, VkPhysicalDevice& physicalDevice, VkCommandPool& commandPool, VkQueue& queue)
{
	//Load Texture
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(filePath.c_str(), &texWidth, &texHeight, &texChannels, stbFormat);
	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}

	int onePixelSize = 0;
	switch (stbFormat)
	{
		case STBI_rgb_alpha:{
			onePixelSize = 4; 
			break; 
		}
		default: {
			throw std::runtime_error("failed to identify stb format!");
		}
	}

	VkDeviceSize imageSize = texWidth * texHeight * onePixelSize;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	VulkanTools::createBuffer(
		imageSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		stagingBuffer,
		stagingBufferMemory,
		*device,
		physicalDevice
	);

	void* data;
	vkMapMemory(*device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(*device, stagingBufferMemory);

	stbi_image_free(pixels);

	//Create Image Obj
	VulkanTools::createImage(
		texWidth,
		texHeight,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		image,
		memory,
		*device,
		physicalDevice
	);

	VulkanTools::transitionImageLayout(
		image,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		commandPool,
		queue,
		*device
	);
	VulkanTools::copyBufferToImage(
		stagingBuffer,
		image,
		static_cast<uint32_t>(texWidth),
		static_cast<uint32_t>(texHeight),
		commandPool,
		queue,
		*device
	);
	VulkanTools::transitionImageLayout(
		image,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		commandPool,
		queue,
		*device
	);

	vkDestroyBuffer(*device, stagingBuffer, nullptr);
	vkFreeMemory(*device, stagingBufferMemory, nullptr);
}
