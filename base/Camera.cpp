/*
* base Camera.cpp
*
* Copyright (C) 2022 by Khasehemwy - github.com/Khasehemwy
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "Camera.h"

Camera::Camera()
{
	camX = pos.x;
	camY = pos.y;
	camZ = pos.z;
}

glm::mat4 Camera::setRotateXZ(float radius)
{
	this->radiusXZ = radius;
	glm::mat4 view(glm::lookAt(pos, pos + front, up));
	return view;
}

glm::mat4 Camera::enableMove(bool enable)
{
	target = pos + front;
	glm::mat4 view = glm::lookAt(pos, target, up);
	return view;
}

glm::mat4 Camera::Move(unsigned int way)
{
	switch (way)
	{
	case 1:
		pos += speed * glm::normalize(glm::cross(up, glm::cross(front, up)));
		break;
	case 2:
		pos -= speed * glm::normalize(glm::cross(up, glm::cross(front, up)));
		break;
	case 3:
		pos -= glm::normalize(glm::cross(front, up)) * speed;
		break;
	case 4:
		pos += glm::normalize(glm::cross(front, up)) * speed;
		break;
	default:
		break;
	}
	target = pos + front;
	this->view = glm::lookAt(pos, target, up);
	return view;
}
