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
class HelloTriangleApplication;

#include "Types.h"
#include "Function.h"
#include "Window.h"
#include "Camera.h"
#include "Input.h"