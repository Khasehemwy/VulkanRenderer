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
	float width, height;
	bool isWindowResize = false;
	std::string title;
	GLFWwindow* window;

public:

	Window(float width = 1920, float height = 1080, const char* title = "Vulkan", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	~Window();
	void windowResize(bool flag);
	bool windowResize();
	std::string getTitle();
	void setTitle(const std::string title);
	GLFWwindow* get();
	float getWidth();
	float getHeight();
};

