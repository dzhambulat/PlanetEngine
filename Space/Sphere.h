#pragma once
#include <glm\glm.hpp>
#include "RoamTerrain.h"
#include "NoiseHelper.h"

class Sphere
{

	public:
	Sphere(double radius)
	{
		this->radius = radius;
		this->terrain = new Roam::RoamTerrain();
		generateOctaedr();
		NoiseHelpers::initPerlin(10);
	}

	glm::vec3* getVertexData(int*);
	void render(glm::vec3 eye);
	~Sphere();
	
private:
	double radius;
	float* generateOctaedr();
	Roam::RoamTerrain* terrain;

};

