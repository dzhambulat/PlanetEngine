#include "Sphere.h"

float* Sphere::generateOctaedr()
{
	float a = this->radius;
	for (int i = 0; i < 8; i++)
		rootNodes[i] = new TreeNode(nullptr, 1);

	rootNodes[0]->points[0] = 0.0f;
	rootNodes[1]->points[0] = a;
	rootNodes[2]->points[0] = 0.0f;

	rootNodes[3]->points[0] = a;
	rootNodes[4]->points[0] = 0.0f;
	rootNodes[5]->points[0] = 0.0f;

	rootNodes[6]->points[0] = 0.0f;
	rootNodes[7]->points[0] = 0.0f;
	rootNodes[8]->points[0] = -a;

	rootNodes[9]->points[0] = 0.0f;
	rootNodes[10]->points[0] = 0.0f;
	rootNodes[11]->points[0] = -a;

	rootNodes[12]->points[0] = 0.0f;
	rootNodes[13]->points[0] = a;
	rootNodes[14]->points[0] = 0.0f;

	rootNodes[15]->points[0] = 0.0f;
	rootNodes[16]->points[0] = a;
	rootNodes[17]->points[0] = 0.0f;

	rootNodes[18]->points[0] = 0.0f;
	rootNodes[19]->points[0] = a;
	rootNodes[20]->points[0] = 0.0f;

	rootNodes[21]->points[0] = 0.0f;
	rootNodes[22]->points[0] = a;
	rootNodes[23]->points[0] = 0.0f;

	float points[72] = { 0.0,a,0.0,a,0.0,0.0,0.0,0.0,-a,
		0.0,0.0,-a,-a,0.0,0.0,0.0,a,0.0,
		0.0,a,0.0,-a,0.0,0.0,0.0,0.0,a,
		0.0,0.0,a,a,0.0,0.0,0.0,a,0.0,
		0.0,-a,0.0,0.0,0.0,-a,a,0.0,0.0,
		a,0.0,0.0,0.0,0.0,a,0.0,-a,0.0,
		0.0,-a,0.0,0.0,0.0,a,-a,0.0,0.0,
		-a,0.0,0.0,0.0,0.0,-a,0.0,-a,0.0 };

	return points;
}

void Sphere::splitTriangle(TreeNode* node)
{

}

void Sphere::reduceTriangle(TreeNode* node)
{

}


Sphere::~Sphere()
{
}

