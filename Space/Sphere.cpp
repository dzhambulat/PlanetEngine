#include "Sphere.h"

float* Sphere::generateOctaedr()
{
	float a = this->radius;

	float points[72] = {
		0.0,0.0,-a,0.0,a,0.0,a,0.0,0.0,
		0.0,a,0.0,0.0,0.0,-a,-a,0.0,0.0,
		0.0,0.0,a,0.0,a,0.0,-a,0.0,0.0,
		0.0,0.0,a,0.0,a,0.0,a,0.0,0.0,
		-a,0.0,0.0,0.0,0.0,-a,0.0,-a,0.0,
		0.0,-a,0.0,0.0,0.0,-a,a,0.0,0.0,
		a,0.0,0.0,0.0,0.0,a,0.0,-a,0.0,
		0.0,-a,0.0,0.0,0.0,a,-a,0.0,0.0
		 };

	NoiseHelpers::initPerlin(4);
	terrain->initialize(points, 72, [](glm::vec3 pos) {  pos /= length(pos); pos *= (6000+NoiseHelpers::perlinValue(pos.x,pos.y,pos.z)); return pos; });
	return points;
}

glm::vec3* Sphere::getVertexData(int* length)
{
	glm::vec3* result;
	*length = terrain->getAllVertices(&result);

	return result;
}

glm::vec3* Sphere::getNormalData(int* length)
{
	glm::vec3* result;
	*length = terrain->getAllNormals(&result);

	return result;
}

void Sphere::render(glm::vec3 eye,glm::vec3 center)
{
	this->terrain->process(eye,center);
}
Sphere::~Sphere()
{
}

