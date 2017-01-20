#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
noperspective out vec4 ppp;
out vec3 pnorm;
uniform mat4 mvp;
void main()
{
   vec4 pos = vec4(pos.x, pos.y, pos.z, 1.0);
	ppp=pos;
        pnorm=norm;
	gl_Position = mvp*pos;
}