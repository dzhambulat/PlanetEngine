#include <iostream>
#define GLEW_STATIC

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Sphere.h"

const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;"
"uniform mat4 mvp;"
"void main()"
"{"
"   vec4 pos = vec4(pos.x, pos.y, pos.z, 1.0);"
"	gl_Position = pos;"
"}";
const GLchar* fragmentShaderSrc =
"#version 330 core\n"
"out vec4 frag_color;"
"void main()"
"{"
"   frag_color = vec4(0.5, 0.5f, 0.4f, 1.0f);"
"}";


GLFWwindow* init(int windowWidth, int windotHeight, const char* windowTitle);

int main()
{
	GLFWwindow* window = init(1024, 760, "Space ship");
	
	GLuint vbo;
	float a = 0.5;
	GLfloat vertices[] = {
		0.0,a,0.0,a,0.0,0.0,0.0,0.0,-a,
		0.0,0.0,-a,-a,0.0,0.0,0.0,a,0.0,
		0.0,a,0.0,-a,0.0,0.0,0.0,0.0,a,
		0.0,0.0,a,a,0.0,0.0,0.0,a,0.0,
		0.0,-a,0.0,0.0,0.0,-a,a,0.0,0.0,
		a,0.0,0.0,0.0,0.0,a,0.0,-a,0.0,
		0.0,-a,0.0,0.0,0.0,a,-a,0.0,0.0,
		-a,0.0,0.0,0.0,0.0,-a,0.0,-a,0.0
	};

	Sphere sphere(3);

	int vertexCount = 0;
	auto verts = sphere.getVertexData(&vertexCount);
	GLfloat* data = new GLfloat[vertexCount * 3];
	for (int i = 0; i < vertexCount; i++)
	{
		data[i * 3] = verts[i].x;
		data[i * 3 + 1] = verts[i].y;
		data[i * 3 + 2] = verts[i].z;
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount*3, data, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	GLuint ibo;

/*	GLuint indices[] = {
		0, 1, 2, 
		0, 2, 3  
	};

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	*/
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertexShaderSrc, NULL);
	glCompileShader(vs);
	GLint result;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
	//	glGetShaderInfoLog(vs, sizeof(infoLog), NULL, infoLog);
		std::cout << "Error! Vertex shader failed to compile. " << std::endl;
	}
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result)
	{

		std::cout << "Error! Vertex shader failed to compile. " <<std::endl;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		std::cout << "Error! Shader program linker failure. "  << std::endl;
	}

	//glm::vec3 pos =glm::vec3(0, 0, -5);
	//glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	//glm::mat4 rot = glm::rotate(glm::mat4(1.0), 2, glm::vec3(0.0, 1.0, 0.0));
//	model = proj*model;
	//GLuint mvp = glGetUniformLocation(program, "mvp");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(program);
		//glUniformMatrix4fv(mvp, 1, GL_FALSE, &model[0][0]);
		glBindVertexArray(vao);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	return 0;
}


void on_keyboard(GLFWwindow* window, int key, int scanCode, int action, int mode)
{

}

void on_window_size(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
GLFWwindow* init(int windowWidth, int windowHeight, const char* windowTitle)
{
	if (!glfwInit())
	{
		std::cout << "GLFW initialization FAILED" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	if (!window)
	{
		std::cout << "Window creation FAILED" << std::endl;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,on_window_size);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization FAILED" << std::endl;
	}

	glfwSetKeyCallback(window, on_keyboard);
	glClearColor(0.5f, 0.23f, 0.33f, 1.0f);
	glViewport(0, 0, windowWidth, windowHeight);

	return window;
}

