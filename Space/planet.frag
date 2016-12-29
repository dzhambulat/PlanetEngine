#version 330 core
in vec4 ppp;
uniform vec3 cam;
out vec4 frag_color;
void main()
{
	vec4 camv=vec4(cam,1.0);
	float len=length(ppp-vec4(0.0,0.0,0.0,1.0));
camv=camv/length(camv);
vec4 pp=ppp/length(ppp);
	
   frag_color = vec4(vec3(0.5,1.0,0.5)*abs(dot(camv,pp)),1.0);
}