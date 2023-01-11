#version 330
 
// Input
in vec2 texcoord;
in vec3 world_position;
in vec3 world_normal;

//in vec3 position;

// Uniforms
uniform sampler2D texture;
uniform vec3 eye_position;
uniform vec3 light_position[1];

uniform int type_of_light;

// Output
layout(location = 0) out vec4 out_color;

float material_shininess = 50;
float material_kd = 0.5;
float material_ks = 0.5;
float cut_off_angle = 30;
vec3 object_light_dir = vec3(0, -1, 0);
float ambient_light = 0.15;

float get_directional_light()
{
	vec3 directional_light_dir = vec3(0, 1, 0);
	
	vec3 N = normalize(world_normal);
	vec3 L = directional_light_dir;
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(-L, normalize(world_normal)));
	
	float diffuse_light = material_kd * max(dot(N, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

	float sun_light = 1 * (diffuse_light + specular_light);

	return sun_light;
}

float get_point_light(vec3 light_position)
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(-L, normalize(world_normal)));

	float diffuse_light = material_kd * max(dot(N, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

	float d						= distance(light_position, world_position);
	float attenuation_factor	= 1 / (1 + d * d);
	float light					= attenuation_factor * (diffuse_light + specular_light);

	return light;
}

float get_spot_light(vec3 light_position)
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(-L, normalize(world_normal)));

	float diffuse_light = material_kd * max(dot(N, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0) {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

	float cut_off_rad		= radians(cut_off_angle);
	float spot_light		= dot(-L, object_light_dir);
	float spot_light_limit	= cos(cut_off_rad);

	float light = 0;
		
	if (spot_light > spot_light_limit) {	
		float d						= distance(light_position, world_position);
		float attenuation_factor	= 1 / (1 + d * d);

		// Quadratic attenuation
		float linear_att		= (spot_light - spot_light_limit) / (1.f - spot_light_limit);
		float light_att_factor	= linear_att * linear_att;
		light					= 5 * attenuation_factor * light_att_factor * (diffuse_light + specular_light);
	}

	return light;
}

void main()
{
	// calculate the out_color using the texture2D() function
	vec4 color1 = texture2D(texture, texcoord);
	
	if (color1.a < .5f)
	{
		discard;
	}

	vec4 color = color1 * get_directional_light();

	// pt point light
	//color += color1 * get_point_light(vec3(0, -4, 5)) * vec4(1, 0, 0, 0);

	// pt spot light
	color += color1 * get_spot_light(vec3(0, -4 , 5)) * vec4(1, 0, 0, 0);

	out_color = color + color1 * ambient_light;
} 