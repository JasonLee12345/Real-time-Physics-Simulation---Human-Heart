#version 330 
#extension GL_ARB_explicit_attrib_location : require 
#extension GL_ARB_explicit_uniform_location : require 

in vec3 interpColor;
out vec4 fragColor;

void main(void) {
	fragColor = vec4(interpColor, 1.0f);
}
