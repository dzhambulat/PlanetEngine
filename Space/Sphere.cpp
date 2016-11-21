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

	for (int i = 0; i < 8; i++)
	{
		rootNodes[i] = new TreeNode(nullptr, 1);
		rootNodes[i]->points[0] = glm::vec3(points[i * 9], points[i * 9 + 1], points[i * 9 + 2]);
		rootNodes[i]->points[1] = glm::vec3(points[i * 9 + 3], points[i * 9 + 4], points[i * 9 + 2 + 5]);
		rootNodes[i]->points[2] = glm::vec3(points[i * 9 + 6], points[i * 9 + 7], points[i * 9 + 2 + 8]);
	}

	return points;
}

glm::vec3* Sphere::getVertexData(int* len)
{
	generateOctaedr();
	glm::vec3* resData[8];
	int resLens[8];
	int dataLen = 0;
	for (int i = 0; i < 8; i++)
	{
		int len;
		glm::vec3* data = rootNodes[i]->generateVertexData(&len);
		resLens[i] = len;
		resData[i] = data;
		dataLen += len;
	}
	glm::vec3* result = new glm::vec3[dataLen];
	int offset = 0;
	for (int i = 0; i < 8; i++)
	{
		memcpy(result + offset*sizeof(glm::vec3), resData[i], resLens[i]*sizeof(glm::vec3));
		offset += resLens[i] * sizeof(glm::vec3);
	}
	*len = dataLen;
	return result;
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

