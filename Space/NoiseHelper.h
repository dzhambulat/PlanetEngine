#pragma once
#include <algorithm>
#include <random>
#include <array>
#include <numeric>

namespace NoiseHelpers
{
	void initPerlin(uint32_t seed);
	double perlinValue(double x, double y, double z);
}