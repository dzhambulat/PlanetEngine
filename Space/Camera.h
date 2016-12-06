#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 eye, center, up;

public:
	Camera();
	Camera(glm::vec3 eye,glm::vec3 center,glm::vec3 up);
	~Camera();

	void setEye(glm::vec3 eye);

	glm::vec3 getEye() const;
	glm::mat4 getMatrix() const;
};

