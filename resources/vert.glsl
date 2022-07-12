#version 450 core

layout(location = 0) in vec3 aPos;

out vec3 color;

uniform mat4 model;
uniform mat4 viewProj;

void main(){
	gl_Position = viewProj * model * vec4(aPos, 1.0);
	color = aPos;
}
