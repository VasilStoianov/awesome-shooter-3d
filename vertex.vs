#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 camera;

void main()
{
     mat4 finalM = projection*camera*transform;
	gl_Position =finalM*vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}