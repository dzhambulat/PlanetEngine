#pragma once
#include <glm/glm.hpp>
#include <GLEW\glew.h>
#include <iostream>
#include <fstream>
#include <string>

namespace ShaderHelper
{
	GLuint createShaderProgram(std::string pathFile);
}