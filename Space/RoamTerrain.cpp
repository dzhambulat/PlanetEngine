#include "RoamTerrain.h"

namespace Roam
{
	RoamTerrain::RoamTerrain()
	{
	}


	RoamTerrain::~RoamTerrain()
	{
	}

	void RoamTerrain::initialize(const float* data, int length, glm::vec3 (*f)(glm::vec3 pos))
	{
		if (length < 3) return;

		this->processFunc = f;
		this->firstNode = make_shared<PolygonNode>();
		shared_ptr<PolygonNode> current = this->firstNode;
		this->polygonCount = length / 9;

		for (int i = 0; i < length / 9; i++)
		{
			current->parent = nullptr;
			current->pointers[0] = glm::vec3(data[i * 9], data[i * 9 + 1], data[i * 9 + 2]);
			current->pointers[1] = glm::vec3(data[i * 9 + 3], data[i * 9 + 4], data[i * 9 + 5]);
			current->pointers[2] = glm::vec3(data[i * 9 + 6], data[i * 9 + 7], data[i * 9 + 8]);

			if (i < length / 9 - 1)
			{
				current->next = make_shared<PolygonNode>();
				current->next->prev = current;
				current = current->next;
			}

			lastNode = current;
		}
	}

	void RoamTerrain::addRenderNode(shared_ptr<PolygonNode> node)
	{
		lastNode->next = node;
		node->prev = lastNode;
		lastNode = node;
	}

	void RoamTerrain::addRenderNodeFirst(shared_ptr<PolygonNode> node)
	{
		firstNode->prev = node;
		node->next = firstNode;
		firstNode = node;
	}

	void RoamTerrain::removeNode(shared_ptr<PolygonNode> node)
	{
		if (node->next != nullptr)
			node->next->prev = node->prev;
		else
			lastNode = node->prev;
		if (node->prev != nullptr)
			node->prev->next = node->next;
		else
			firstNode = node->next;
	}

	void RoamTerrain::splitPolygon(shared_ptr<PolygonNode> node)
	{
		vec3 fs = node->pointers[1] - node->pointers[0];
		fs /= 2;
		fs += node->pointers[0];
		fs = processFunc(fs);
		
		vec3 st = node->pointers[2] - node->pointers[1];
		st /= 2;
		st += node->pointers[1];
		st = processFunc(st);

		vec3 ft = node->pointers[0] - node->pointers[2];
		ft /= 2;
		ft += node->pointers[2];
		ft = processFunc(ft);

		int newLod = node->lod + 1;
		node->firstChild = make_shared<PolygonNode>(node, newLod);
		node->firstChild->pointers[0] = node->pointers[0];
		node->firstChild->pointers[1] = fs;
		node->firstChild->pointers[2] = ft;

		node->secondChild = make_shared<PolygonNode>(node, newLod);
		node->secondChild->pointers[0] = fs;
		node->secondChild->pointers[1] = node->pointers[1];
		node->secondChild->pointers[2] = st;

		node->thirdChild = make_shared<PolygonNode>(node, newLod);
		node->thirdChild->pointers[0] = ft;
		node->thirdChild->pointers[1] = st;
		node->thirdChild->pointers[2] = node->pointers[2];

		node->centerChild = make_shared<PolygonNode>(node, newLod);
		node->centerChild->pointers[0] = st;
		node->centerChild->pointers[1] = ft;
		node->centerChild->pointers[2] = fs;

		addRenderNodeFirst(node->firstChild);
		addRenderNodeFirst(node->secondChild);
		addRenderNodeFirst(node->thirdChild);
		addRenderNodeFirst(node->centerChild);
		node->firstChild->splitted = node->secondChild->splitted = node->thirdChild->splitted = node->centerChild->splitted = true;
		this->polygonCount += 3;
		removeNode(node);
	}

	void RoamTerrain::reducePolygon(shared_ptr<PolygonNode> node)
	{
		shared_ptr<PolygonNode> parent = node->parent;

		removeNode(parent->firstChild);
		removeNode(parent->secondChild);
		removeNode(parent->thirdChild);
		removeNode(parent->centerChild);

		addRenderNodeFirst(parent);
	}

	float RoamTerrain::getTreshholdDistance(int lod) const
	{
		return 30.0/pow(2, lod-1);
	}

	float RoamTerrain::getDistanceFromPolygon(glm::vec3 eye, shared_ptr<PolygonNode> polygonNode) const
	{
		glm::vec3 polygonCenter = (polygonNode->pointers[0] + polygonNode->pointers[1] + polygonNode->pointers[2]);
		polygonCenter /= 3;
		
		return glm::length(polygonCenter - eye);
	}
	void RoamTerrain::process(glm::vec3 eye)
	{
		shared_ptr<PolygonNode> current = firstNode;

		while (current != nullptr)
		{
			double dist = getDistanceFromPolygon(eye, current);
			double treshhold = getTreshholdDistance(current->lod);
			if (dist> 0.1 && dist < treshhold )
			{
				splitPolygon(current);
			}
			else if (current->lod > 1)
			{
				treshhold = getTreshholdDistance(current->lod - 1);
					if (dist > treshhold)
					{
						reducePolygon(current);
					}
			}
			current = current->next;
		}
	}
	int RoamTerrain::getAllVertices(vec3** result) const
	{
		int vertexCount = polygonCount * 3;
		vec3* data = new vec3[vertexCount];

		shared_ptr<PolygonNode> current = firstNode;
		int index = 0;
		while (current != nullptr)
		{
			data[index] = current->pointers[0];
			data[index + 1] = current->pointers[1];
			data[index + 2] = current->pointers[2];
			current = current->next;
			index += 3;
		}
		*result = data;

		return vertexCount;
	}
}
