/*
* base Input.cpp
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Input.h"
static Camera* Input_g_camera;
float Input_g_lastX, Input_g_lastY;
float Input_g_pitch, Input_g_yaw;
static float* Input_g_fov;

void Input_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xOffset = xpos - Input_g_lastX;
	float yOffset = Input_g_lastY - ypos;
	Input_g_lastX = xpos;
	Input_g_lastY = ypos;
	float sensitivity = 0.05f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;
	Input_g_yaw += xOffset;
	Input_g_pitch += yOffset;
	if (Input_g_pitch > 89.0f)
		Input_g_pitch = 89.0f;
	if (Input_g_pitch < -89.0f)
		Input_g_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(Input_g_pitch)) * cos(glm::radians(Input_g_yaw));
	front.y = sin(glm::radians(Input_g_pitch));
	front.z = cos(glm::radians(Input_g_pitch)) * sin(glm::radians(Input_g_yaw));
	Input_g_camera->front = glm::normalize(front);
}

void Input_scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	*Input_g_fov -= yOffset;
	if (*Input_g_fov <= 1.0f)*Input_g_fov = 1.0f;
	if (*Input_g_fov >= 60.0f)*Input_g_fov = 60.0f;
}

Input::Input(Window* window, Camera* camera)
{
	this->window = window;
	this->camera = camera;
	Input_g_camera = camera;
}

void Input::EnableCursor()
{
	glfwSetInputMode(window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window->get(), Input_mouse_callback);
	float lastX = (float)window->getWidth() / 2;
	float lastY = (float)window->getHeight() / 2;
	Input_g_lastX = lastX; Input_g_lastY = lastY;
}

void Input::EnableScroll(float* fov)
{
	if (*fov <= 0.01f) { *fov = 45.0f; }
	Input_g_fov = fov;
	glfwSetScrollCallback(window->get(), Input_scroll_callback);
}

void Input::ProcessInput()
{
	if (glfwGetKey(window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window->get(), true);
	}

	if (glfwGetKey(window->get(), GLFW_KEY_W) == GLFW_PRESS)
		camera->Move(1);
	if (glfwGetKey(window->get(), GLFW_KEY_S) == GLFW_PRESS)
		camera->Move(2);
	if (glfwGetKey(window->get(), GLFW_KEY_A) == GLFW_PRESS)
		camera->Move(3);
	if (glfwGetKey(window->get(), GLFW_KEY_D) == GLFW_PRESS)
		camera->Move(4);
}
