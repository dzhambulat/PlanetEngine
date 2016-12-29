#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 eye, center, up,right;

public:
	Camera();
	Camera(glm::vec3 eye,glm::vec3 center,glm::vec3 up);
	~Camera();

	void setEye(glm::vec3 eye);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void moveForward(float step);

	glm::vec3 getEye() const;
	glm::vec3 getCenter() const;
	glm::mat4 getMatrix() const;
};

