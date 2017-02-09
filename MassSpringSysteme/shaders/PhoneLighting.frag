#version 330 
#extension GL_ARB_explicit_attrib_location : require 
#extension GL_ARB_explicit_uniform_location : require 

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;

/* Uniform variables for Camera and Light Direction */ 
uniform mat4 modelViewMatrix;

struct Light {
	vec3 position;
	vec3 target;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float exponent;
	float cutoff;
};

uniform Light light0;
uniform Light light1;
uniform Light light2;

in vec3 interpSurfaceNormal;
in vec3 interpVertexPosition;
in vec2 interpTextureCoord;

/* Light direction in tangent space */
in vec3 light0_position_eye;
in vec3 light0_target_eye;
in vec3 lightVector0;

layout( location = 0 ) out vec4 fragColor;

vec4 calculation_values() {

	vec3 fragmentNormal = normalize(texture2D(normalTexture, interpTextureCoord).xyz * 2.0 - 1.0);

	vec3 spotLight0_dir_eye =  normalize(light0_target_eye - light0_position_eye);
	vec3 spotLight0_pos_eye = light0_position_eye;

	vec3 l = normalize(spotLight0_pos_eye - interpVertexPosition);
	vec3 c = normalize(-interpVertexPosition);
	vec3 r = normalize(-reflect(l, interpSurfaceNormal));

	float angle0 = acos( dot(spotLight0_dir_eye, -l) );
	float cutoff0 = radians( clamp(light0.cutoff, 0.0, 90.0) );

	//-------------------------------------------------------------------------- 
    // Light and material properties.
    //-------------------------------------------------------------------------- 
    vec4 Ia0 = vec4(light0.ambient, 1.0f);
    vec4 Id0 = vec4(light0.diffuse, 1.0f);
    vec4 Is0 = vec4(light0.specular, 1.0f);
 
    vec4 Ka = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 Kd = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 Ks = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float shininess = 16.0f;
 
    vec4 Iambient = vec4(0.0f);
    vec4 Idiffuse = vec4(0.0f);
    vec4 Ispecular = vec4(0.0f);

	//-------------------------------------------------------------------------- 
	// Assigning actual color values.
	//-------------------------------------------------------------------------- 
	Iambient = 0.2 * (Ia0 * Ka);
	
	if (angle0 < cutoff0) {
		float lambertComponent = max(0.0f, dot(fragmentNormal, lightVector0));
		Idiffuse = texture2D(diffuseTexture, interpTextureCoord);
		Idiffuse *= (Id0 * Kd) * lambertComponent;

		Ispecular = (Is0 * Ks) * pow(max(dot(r, c), 0.0f), shininess);
		Ispecular *= texture2D(specularTexture, interpTextureCoord);

		float spotFactor0 = pow( dot(-l, spotLight0_dir_eye), light0.exponent );
		Iambient += spotFactor0 * (Idiffuse + Ispecular);
	}

	vec4 ColorCombined = Iambient;
	ColorCombined += 0.5 * texture2D(diffuseTexture, interpTextureCoord);
	return ColorCombined;
}

void main(void) {
	vec4 color = calculation_values();
	fragColor = vec4(color);
}