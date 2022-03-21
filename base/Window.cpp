/*
* base Window.cpp
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Window.h"

void framebufferResizeCallback(GLFWwindow* window, int width, int height) 
{
    auto windowClass = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    windowClass->windowResize(true);
}

Window::Window(float width, float height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
    :width(width),
    height(height)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

GLFWwindow* Window::get()
{
    return this->window;
}

void Window::windowResize(bool flag)
{
    this->isWindowResize = flag;
}

bool Window::windowResize()
{
    return isWindowResize;
}

float Window::getWidth()
{
    return this->width;
}

float Window::getHeight()
{
    return this->height;
}

