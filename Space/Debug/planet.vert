#version 330 core
layout (location = 0) in vec3 pos;
out vec4 ppp;
uniform mat4 mvp;
void main()
{
   vec4 pos = vec4(pos.x, pos.y, pos.z, 1.0);
	ppp=pos;
	gl_Position = mvp*pos;
}