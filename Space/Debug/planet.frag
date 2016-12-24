#version 330 core
in vec4 ppp;
out vec4 frag_color;
void main()
{
	float len=length(ppp-vec4(0.0,0.0,0.0,1.0));
   frag_color = vec4(0.1,(len-6000)/500.0,0.1,1.0);
}