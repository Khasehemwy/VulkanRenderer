/*
* base Input.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#include "VulkanBase.h"

class Input
{
private:
	Window* window;
	Camera* camera;
public:
	Input(Window* window, Camera* camera);
	virtual ~Input() = default;
	void EnableCursor();
	void EnableScroll(float* fov);
	void ProcessInput();
};