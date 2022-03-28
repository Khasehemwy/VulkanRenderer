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
	case 1://W
		pos += speed * glm::normalize(glm::cross(up, glm::cross(front, up)));
		break;
	case 2://S
		pos -= speed * glm::normalize(glm::cross(up, glm::cross(front, up)));
		break;
	case 3://A
		pos -= glm::normalize(glm::cross(front, up)) * speed;
		break;
	case 4://D
		pos += glm::normalize(glm::cross(front, up)) * speed;
		break;
	case 5://Q
		pos += up * speed;
		break;
	case 6://E
		pos += -up * speed;
		break;
	default:
		break;
	}
	target = pos + front;
	this->view = glm::lookAt(pos, target, up);
	return view;
}
