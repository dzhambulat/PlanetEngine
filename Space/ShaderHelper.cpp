#include "ShaderHelper.h"
namespace ShaderHelper
{
	GLuint createShaderProgram(std::string pathFile)
	{
		std::ifstream shaderFs(pathFile + ".vert");
		std::string line;
		std::string shaderSrc;
		while (!std::getline(shaderFs, line).eof())
		{
			shaderSrc.append(line+"\n");
		}
		shaderSrc.append(line);
		auto vertPtr = shaderSrc.c_str();
		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertPtr, NULL);
		glCompileShader(vs);
		GLint result;

		glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			//	glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
			std::cout << "Error! Vertex shader failed to compile. " << std::endl;
		}

		std::ifstream fragmentShaderFs(pathFile + ".frag");
		std::string fragShaderSrc;
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		while (!std::getline(fragmentShaderFs, line).eof())
		{
			fragShaderSrc.append(line+"\n");
		}
		fragShaderSrc.append(line);
		auto fragPtr = fragShaderSrc.c_str();
		glShaderSource(fs, 1, &fragPtr, NULL);
		glCompileShader(fs);
		glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
		if (!result)
		{

			std::cout << "Error! Fragment shader failed to compile. " << std::endl;
		}

		GLuint program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		return program;
	}
}