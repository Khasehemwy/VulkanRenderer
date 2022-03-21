/*
* base Camera.h
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 direction = glm::normalize(pos - target);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), direction));
	glm::vec3 up = glm::cross(direction, right);
	glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ), target, up);

	float speed = 0.02f;

	float radiusXZ = 0;
	float camX, camY, camZ;

	Camera();
	glm::mat4 setRotateXZ(float radius);
	glm::mat4 enableMove(bool enable);
	glm::mat4 Move(unsigned int way);
};