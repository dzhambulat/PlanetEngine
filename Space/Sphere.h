#pragma once
#include <glm\glm.hpp>
#include "RoamTerrain.h"

class Sphere
{

	public:
	Sphere(double radius)
	{
		this->radius = radius;
		this->terrain = new Roam::RoamTerrain();
		generateOctaedr();
	}

	glm::vec3* getVertexData(int*);
	void render(glm::vec3 eye);
	~Sphere();

private:
	double radius;
	float* generateOctaedr();
	Roam::RoamTerrain* terrain;

};

