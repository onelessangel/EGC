#version 330
 
// Input
in vec2 texcoord;
//in vec3 position;
in vec3 world_position;
in vec3 world_normal;


// Uniforms
uniform sampler2D texture;
//uniform vec3 light_position;

uniform vec3 eye_position;
//uniform float material_kd;
//uniform float material_ks;
//uniform int material_shininess;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
	// calculate the out_color using the texture2D() function
	vec4 colour1 = texture2D(texture, texcoord);
	
	if (colour1.a < .5f)
	{
		discard;
	}

	//vec3 light_position = vec3(0, 5, 0);
	float material_shininess = 50;
	float material_kd = 0.5;
	float material_ks = 0.5;

	vec3 colour_light = vec3(1, 1, 1);
	vec3 N = normalize(world_normal);
	vec3 L = vec3(0, 1, 0);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	
	float ambient_light = 0.3;
	float diffuse_light = material_kd * ambient_light * max(dot(world_normal, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0)
    {
        specular_light = material_ks * ambient_light * pow(max(dot(V, R), 0), material_shininess);
    }

	//float d = distance(light_position, position);
    //float attenuation_factor = 1 / (1 + 0.14 * d + 0.07 * d * d);
    //float light = ambient_light + 15 * attenuation_factor * (diffuse_light + specular_light);

	float light = ambient_light + 5 * (diffuse_light + specular_light);

	out_color = colour1 * light;
}