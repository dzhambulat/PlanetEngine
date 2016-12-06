#include "Camera.h"



Camera::Camera()
{
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) :eye(eye), center(center), up(up)
{
}


Camera::~Camera()
{
}

glm::vec3 Camera::getEye() const
{
	return this->eye;
}

glm::mat4 Camera::getMatrix() const
{
	return glm::lookAt(this->eye, this->center, this->up);
}

void Camera::setEye(glm::vec3 eye)
{
	this->eye = eye;
}