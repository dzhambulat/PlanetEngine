#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Camera.h"
#include <memory>
#include <iostream>
#include <tuple>

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

			PolygonNode(vec3 p1,vec3 p2,vec3 p3)
			{
				pointers[0] = p1;
				pointers[1] = p2;
				pointers[2] = p3;
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
			vec3 normal[3];
			bool splitted = false;
			int lod = 1;
			bool isPatch = false;
			shared_ptr<PolygonNode> firstChild, secondChild, thirdChild, centerChild; //clockwise
			shared_ptr<PolygonNode> parent;
			shared_ptr<PolygonNode> firstNeigh, secondNeigh, thirdNeigh;
			shared_ptr<PolygonNode> patchNode1, patchNode2;
			shared_ptr<PolygonNode> next, prev;
		};


	private:

		double trashes[18] = {50000,30000,20000,10000,5000,1000,500,200,100,80,60,50,30,20,15,10};
		glm::vec3 (*processFunc)(glm::vec3 pos);
		shared_ptr<PolygonNode> lastNode;
		shared_ptr<PolygonNode> firstNode;
		void splitPolygon(shared_ptr<PolygonNode> polygonNode);
		void reducePolygon(shared_ptr<PolygonNode> polygonNode);
		void addRenderNode(shared_ptr<PolygonNode> polygonNode);
		void removeNode(shared_ptr<PolygonNode> polygonNode);
		void splitPolygon(shared_ptr<PolygonNode> polygonNode, int endLod);
		void createPatch(shared_ptr<PolygonNode> polygonNode, int sideNum, glm::vec3 point);
		void setNeighboursForChild(shared_ptr<PolygonNode> polygon1, shared_ptr<PolygonNode> polygon2, int side);
		void RoamTerrain::addRenderNodeFirst(shared_ptr<PolygonNode> node);

		float getTreshholdDistance(int lod) const;
		std::tuple<int,int> findBorders(shared_ptr<PolygonNode> fnode, shared_ptr<PolygonNode> snode) const;
		float getDistanceFromPolygon(glm::vec3 eye,shared_ptr<PolygonNode> polygonNode) const;
		int polygonCount = 0;
	public:
		RoamTerrain();
		~RoamTerrain();

		void initialize(const float* data, int length, glm::vec3 (*f)(glm::vec3 pos)); // initialize with pointers data
		void process(glm::vec3 eye,glm::vec3 center);
		
		int getAllVertices(vec3** data) const; 
		int getAllNormals(vec3** data) const;


	};
}