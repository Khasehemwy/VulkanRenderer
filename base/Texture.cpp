/*
* base Texture.cpp
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Texture.h"

Texture::~Texture()
{
	if (pDevice) {
		vkDestroySampler(*pDevice, sampler, nullptr);
		vkDestroyImageView(*pDevice, view, nullptr);
		vkDestroyImage(*pDevice, image, nullptr);
		vkFreeMemory(*pDevice, memory, nullptr);
	}
}

Texture2D::Texture2D(VkDevice* device)
{
	this->pDevice = device;
}

void Texture2D::loadFromFile(std::string filePath, int stbFormat, VkPhysicalDevice& physicalDevice, VkCommandPool& commandPool, VkQueue& queue, VkFormat format)
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
		*pDevice,
		physicalDevice
	);

	void* data;
	vkMapMemory(*pDevice, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(*pDevice, stagingBufferMemory);

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
		*pDevice,
		physicalDevice
	);

	VulkanTools::transitionImageLayout(
		image,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		commandPool,
		queue,
		*pDevice
	);
	VulkanTools::copyBufferToImage(
		stagingBuffer,
		image,
		static_cast<uint32_t>(texWidth),
		static_cast<uint32_t>(texHeight),
		commandPool,
		queue,
		*pDevice
	);
	VulkanTools::transitionImageLayout(
		image,
		VK_FORMAT_R8G8B8A8_SRGB,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		commandPool,
		queue,
		*pDevice
	);

	vkDestroyBuffer(*pDevice, stagingBuffer, nullptr);
	vkFreeMemory(*pDevice, stagingBufferMemory, nullptr);

	//Create image view
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	if (vkCreateImageView(*pDevice, &viewInfo, nullptr, &view) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture image view!");
	}

	//Create sampler
	VkSamplerCreateInfo samplerInfo{};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	VkPhysicalDeviceProperties properties{};
	vkGetPhysicalDeviceProperties(physicalDevice, &properties);
	samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	if (vkCreateSampler(*pDevice, &samplerInfo, nullptr, &sampler) != VK_SUCCESS) {
		throw std::runtime_error("failed to create texture sampler!");
	}
}
