#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <memory>

using namespace glm;
using namespace std;

namespace Roam
{
	class RoamTerrain
	{
		struct PolygonNode
		{
			PolygonNode()
			{
				parent = nullptr;
				firstChild = secondChild = thirdChild = centerChild = nullptr;
			}

			PolygonNode(shared_ptr<PolygonNode> node):PolygonNode()
			{
				parent = node;
			}

			vec3 pointers[3];
			bool splitted = false;
			shared_ptr<PolygonNode> firstChild, secondChild, thirdChild, centerChild; //clockwise
			shared_ptr<PolygonNode> parent;

			shared_ptr<PolygonNode> next, prev;
		};


	private:
		shared_ptr<PolygonNode> lastNode;
		shared_ptr<PolygonNode> firstNode;
		void splitPolygon(shared_ptr<PolygonNode> polygonNode);
		void reducePolygon(PolygonNode* polygonNode);
		void addRenderNode(shared_ptr<PolygonNode> polygonNode);
		void RoamTerrain::addRenderNodeFirst(shared_ptr<PolygonNode> node);
		float getDistanceFromPolygon(glm::vec3 eye,shared_ptr<PolygonNode> polygonNode) const;
		int polygonCount = 0;
	public:
		RoamTerrain();
		~RoamTerrain();

		void initialize(const float* data, int length); // initialize with pointers data
		void process(glm::vec3 eye);

		int getAllVertices(vec3** data) const; 


	};
}