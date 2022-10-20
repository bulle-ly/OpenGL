#shader vertex 
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_Mvp;
void main()
{
	gl_Position = u_Mvp * position;
	
};

#shader fragment 
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
void main()
{
	color = u_Color;
};



