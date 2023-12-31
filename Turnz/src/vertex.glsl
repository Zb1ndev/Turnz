#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

out vec3 v_colors;

void main() {
	v_colors = color;
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}