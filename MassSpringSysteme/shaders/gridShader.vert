#version 330 
#extension GL_ARB_explicit_attrib_location : require 
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

out vec3 interpColor;

void main(void) {
	interpColor = color;
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0f);
}