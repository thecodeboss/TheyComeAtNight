#version 150 core

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

in layout(location=0) vec3 in_Position;
in layout(location=1) vec4 in_Color;

out vec4 pass_Color;

void main(void)
{  
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position, 1.0);
	pass_Color = in_Color;
}
