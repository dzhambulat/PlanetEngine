#pragma once
class Sphere
{
public:
	Sphere(double radius)
	{
		this->radius = radius;
	}

	~Sphere();

private:
	double radius;
	const float OFACTOR = 0.7071067f;
	float* generateOctaedr();
};

