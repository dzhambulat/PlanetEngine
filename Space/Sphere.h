#pragma once
#include <glm\glm.hpp>

class Sphere
{
	class TreeNode
	{
	public:
		int levelOfDetail;
		TreeNode* centerNode, *leftNode, *rightNode, *topNode, *parentNode;
		glm::vec3 points[3];

		TreeNode(TreeNode* parentNode,int lod)
		{
			this->parentNode = parentNode;
			this->levelOfDetail = lod;
			centerNode = leftNode = rightNode = topNode = nullptr;
		}
		bool isSplitOk()
		{
			return centerNode == nullptr;
		}

		void addLeftNode(glm::vec3 points[3])
		{
			leftNode = new TreeNode(this, levelOfDetail + 1);
			memcpy(leftNode->points, points, sizeof(glm::vec3));
		}
		void addRightNode(glm::vec3 points[3])
		{
			rightNode = new TreeNode(this, levelOfDetail + 1);
			memcpy(rightNode->points, points, sizeof(glm::vec3));
		}
		void addTopNode(glm::vec3 points[3])
		{
			topNode = new TreeNode(this, levelOfDetail + 1);
			memcpy(topNode->points, points, sizeof(glm::vec3));
			
		}
		void addCenterNode(glm::vec3 points[3])
		{
			centerNode = new TreeNode(this, levelOfDetail + 1);
			memcpy(centerNode->points, points, sizeof(glm::vec3));
		}

		glm::vec3* generateVertexData(int* len)
		{
			if (centerNode != nullptr)
			{
				int cn, ln, rn, tn;
				auto centerPoints = centerNode->generateVertexData(&cn);
				auto leftPoints = leftNode->generateVertexData(&ln);
				auto rightPoints = centerNode->generateVertexData(&rn);
				auto topPoints = leftNode->generateVertexData(&tn);

				*len = cn + ln + rn + tn;
				glm::vec3* points = new glm::vec3[*len];
				memcpy(points, centerPoints, *len * sizeof(glm::vec3));

				return points;

			}
			else
			{
				*len = 3;
				return this->points;
			}

		}
		~TreeNode()
		{
			delete[] points;
		}
	};

	public:
	Sphere(double radius)
	{
		this->radius = radius;
	}

	glm::vec3* getVertexData(int*);
	~Sphere();

private:
	double radius;
	float* generateOctaedr();
	TreeNode* rootNodes[8];

	void splitTriangle(TreeNode* node);
	void reduceTriangle(TreeNode* node);

};

