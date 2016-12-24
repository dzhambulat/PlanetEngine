#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <memory>
#include <iostream>
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

			PolygonNode(shared_ptr<PolygonNode> node,int lod):PolygonNode()
			{
				parent = node;
				this->lod = lod;
			}

			~PolygonNode()
			{
			//	cout << "remove";
			}
			vec3 pointers[3];
			bool splitted = false;
			int lod = 1;
			shared_ptr<PolygonNode> firstChild, secondChild, thirdChild, centerChild; //clockwise
			shared_ptr<PolygonNode> parent;

			shared_ptr<PolygonNode> next, prev;
		};


	private:

		int trashes[10] = {100000,90000,80000,50000,25000,10000,5000,2000,1000,500};
		glm::vec3 (*processFunc)(glm::vec3 pos);
		shared_ptr<PolygonNode> lastNode;
		shared_ptr<PolygonNode> firstNode;
		void splitPolygon(shared_ptr<PolygonNode> polygonNode);
		void reducePolygon(shared_ptr<PolygonNode> polygonNode);
		void addRenderNode(shared_ptr<PolygonNode> polygonNode);
		void removeNode(shared_ptr<PolygonNode> polygonNode);
		void splitPolygon(shared_ptr<PolygonNode> polygonNode, int endLod);
		float getTreshholdDistance(int lod) const;
		void RoamTerrain::addRenderNodeFirst(shared_ptr<PolygonNode> node);
		float getDistanceFromPolygon(glm::vec3 eye,shared_ptr<PolygonNode> polygonNode) const;
		int polygonCount = 0;
	public:
		RoamTerrain();
		~RoamTerrain();

		void initialize(const float* data, int length, glm::vec3 (*f)(glm::vec3 pos)); // initialize with pointers data
		void process(glm::vec3 eye);
		
		int getAllVertices(vec3** data) const; 


	};
}