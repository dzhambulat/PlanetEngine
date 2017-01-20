#version 330 core
noperspective in vec4 ppp;
in vec3 pnorm;
uniform vec3 cam;
out vec4 frag_color;
void main()
{
vec4 fc=vec4(1.0,1.0,1.0,1.0);
vec4 sc=vec4(0.2,0.2,0.2,1.0);
	vec4 camv=vec4(cam,1.0);
	float len=length(ppp-vec4(0.0,0.0,0.0,1.0));
camv=camv/length(camv);
vec4 pp=ppp/length(ppp);
vec3 lightDir=vec3(0.0,0.0,1.0);
float s = dot(lightDir,pnorm);
  // frag_color = vec4(vec3(0.5,1.0,0.5)*abs(dot(camv,pp)),1.0);
//frag_color = vec4(vec3(s,s,s),1.0);
float h=length(ppp)-6000;
frag_color=mix(fc,sc,h/20.0);
}