#include "Camera.h"
#include <iostream>


Camera::Camera()
{
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) :eye(eye), center(center), up(up)
{
	glm::vec3 unit = this->center - this->eye;
	unit /= glm::length(unit);

	this->right = glm::cross(unit, up);
}


Camera::~Camera()
{
}

glm::vec3 Camera::getEye() const
{
	return this->eye;
}

glm::vec3 Camera::getCenter() const
{
	return this->center;
}

glm::mat4 Camera::getMatrix() const
{
	return glm::lookAt(this->eye, this->center, this->up);
}

void Camera::setEye(glm::vec3 eye)
{
	this->eye = eye;
}

void Camera::moveForward(float step)
{
	glm::vec3 unit = this->center - this->eye;
	unit /= glm::length(unit);
	unit *= step;
	this->eye += unit;
	this->center += unit;
}
void Camera::rotateX(float angle)
{
	glm::mat4x4 m = glm::rotate(glm::mat4x4(1.0), angle, this->right);
	glm::mat4x4 trm = glm::translate(glm::mat4x4(1.0), -this->eye);
	glm::mat4x4 itrm = glm::translate(glm::mat4x4(1.0), this->eye);
	glm::vec4 v = glm::vec4(this->center, 1);
	glm::vec4 u = glm::vec4(this->up, 1);
	v = itrm*m*trm*v;
	u = m*u;

	this->up = u;
	this->center = glm::vec3(v.x, v.y, v.z);

}
void Camera::rotateY(float angle)
{
	glm::mat4x4 m = glm::rotate(glm::mat4x4(1.0), angle, this->up);
	glm::mat4x4 trm = glm::translate(glm::mat4x4(1.0), -this->eye);
	glm::mat4x4 itrm = glm::translate(glm::mat4x4(1.0), this->eye);
	glm::vec4 v = glm::vec4(this->center, 1);
	glm::vec4 u = glm::vec4(this->up, 1);
	glm::vec4 r = glm::vec4(this->right, 1);
	v = itrm*m*trm*v;
	u = m*u;
	r = m*r;

	this->right = r;
	this->up = glm::vec3(u.x, u.y, u.z);
	this->center = glm::vec3(v.x, v.y, v.z);
}

void Camera::rotateZ(float angle)
{
	glm::vec3 unit = this->center - this->eye;
	unit /= glm::length(unit);
	glm::mat4x4 m = glm::rotate(glm::mat4x4(1.0), angle, unit);
	glm::mat4x4 trm = glm::translate(glm::mat4x4(1.0), -this->eye);
	glm::mat4x4 itrm = glm::translate(glm::mat4x4(1.0), this->eye);
	glm::vec4 v = glm::vec4(this->center, 1);
	glm::vec4 u = glm::vec4(this->up, 1);
	v = trm*m*itrm*v;
	u = m*u;
	glm::vec4 r = glm::vec4(this->right, 1);
	r = m*r;

	this->right = r;
	this->up = u;
	this->center = glm::vec3(v.x, v.y, v.z);
}