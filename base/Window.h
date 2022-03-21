/*
* base Window.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "VulkanBase.h"

class Window
{
private:
	float width = 1400, height = 800;
	bool isWindowResize = false;
	GLFWwindow* window;

public:

	Window(float width = 1400, float height = 800, const char* title = "Vulkan", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	GLFWwindow* get();
	void windowResize(bool flag);
	bool windowResize();
	float getWidth();
	float getHeight();
};

