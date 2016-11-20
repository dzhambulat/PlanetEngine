#pragma once
class Sphere
{
	class TreeNode
	{
	public:
		int levelOfDetail;
		TreeNode* centerNode, *leftNode, *rightNode, *topNode, *parentNode;
		float* points;

		TreeNode(TreeNode* parentNode,int lod)
		{
			this->parentNode = parentNode;
			this->levelOfDetail = lod;
			centerNode = leftNode = rightNode = topNode = nullptr;
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

	~Sphere();

private:
	double radius;
	float* generateOctaedr();
	TreeNode* rootNodes[8];

	void splitTriangle(TreeNode* node);
	void reduceTriangle(TreeNode* node);

};

