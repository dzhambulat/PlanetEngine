#include <iostream>
#define GLEW_STATIC

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>
#include "Sphere.h"

const GLchar* vertexShaderSrc =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;"
"void main()"
"{"
"   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
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

//	Sphere sphere(5)
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(program);
		glBindVertexArray(vao);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glDrawArrays(GL_TRIANGLES, 0, 24);
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

