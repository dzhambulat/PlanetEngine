#include "Sphere.h"

float* Sphere::generateOctaedr()
{
	float a = this->radius;

	float points[72] = { 0.0,a,0.0,a,0.0,0.0,0.0,0.0,-a,
		0.0,0.0,-a,-a,0.0,0.0,0.0,a,0.0,
		0.0,a,0.0,-a,0.0,0.0,0.0,0.0,a,
		0.0,0.0,a,a,0.0,0.0,0.0,a,0.0,
		0.0,-a,0.0,0.0,0.0,-a,a,0.0,0.0,
		a,0.0,0.0,0.0,0.0,a,0.0,-a,0.0,
		0.0,-a,0.0,0.0,0.0,a,-a,0.0,0.0,
		-a,0.0,0.0,0.0,0.0,-a,0.0,-a,0.0 };

	terrain->initialize(points, 72);
	return points;
}

glm::vec3* Sphere::getVertexData(int* length)
{
	glm::vec3* result;
	*length = terrain->getAllVertices(&result);

	return result;
}
Sphere::~Sphere()
{
}

