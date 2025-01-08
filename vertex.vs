#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 projection;

void main()
{

	mat4 proj = mat4(
		0.750000, 0.000000, 0.000000, 0.000000, 
0.000000, 1.000000, 0.000000, 0.000000, 
0.000000, 0.000000, -1.002002, -1.000000, 
0.000000, 0.000000, -0.200200, 0.000000);
	gl_Position =projection*transform*vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}