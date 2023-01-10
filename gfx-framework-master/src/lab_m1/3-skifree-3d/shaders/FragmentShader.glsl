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

float get_directional_light() {
	vec3 directional_light_dir = vec3(1, 1, 0);
	
	//vec3 color_light = vec3(1, 1, 1);
	vec3 N = normalize(world_normal);
	vec3 L = directional_light_dir;
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(-L, normalize(world_normal)));
	
	float diffuse_light = material_kd * max(dot(N, L), 0);
	float specular_light = 0;

	if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

	float sun_light = 2 * (diffuse_light + specular_light);

	return sun_light;
}

float get_point_light(vec3 light_position) {
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);
	float specular_light = 0;

	if (diffuse_light > 0) {
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	float d						= distance(light_position, world_position);
	float attenuation_factor	= 1 / (d + 1);
	float light					= attenuation_factor * (diffuse_light + specular_light);

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

	color += color1 * get_point_light(vec3(0, -4, 5)) * vec4(1, 0, 0, 0);
	
	/*for (int i = 0; i < 1; i++) {
		vec3 N1 = normalize(world_normal);
		vec3 L1 = normalize(light_position[i] - world_position);
		vec3 V1 = normalize(eye_position - world_position);
		vec3 H1 = normalize(L1 + V1);
		vec3 R1 = normalize(reflect(L1, world_normal));

		//float ambient_light = 0.3;
		//float diffuse_light = material_kd * max(dot(normalize(N1), L1), 0.f);
		//float specular_light = 0;
		
		//if (diffuse_light > 0) {
		//	specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
		//}

		float light = 0.f;

		if (type_of_light == 1)
		{
			float cut_off_rad		= radians(cut_off_angle);
			float spot_light		= dot(-L1, object_light_dir);
			float spot_light_limit	= cos(cut_off_rad);
		
			if (spot_light > spot_light_limit)
			{	
				float d						= distance(light_position, world_position);
				float attenuation_factor	= 1 / (d * d + 1);
				// Quadratic attenuation
				float linear_att		= (spot_light - spot_light_limit) / (1.f - spot_light_limit);
				float light_att_factor	= linear_att * linear_att;
				light					= attenuation_factor * light_att_factor * (diffuse_light + specular_light);
			} else
			{
				light = 0;  // There is no spot light, but there is light from other objects
			}
		} else
		{
			
		}

		// TODO(student): Compute the total light. You can just add the components
		// together, but if you're feeling extra fancy, you can add individual
		// colors to the light components. To do that, pick some vec3 colors that
		// you like, and multiply them with the respective light components.
		color += color1 * (light);
	}*/

	//out_color = color1 * ambient_light + color;
	out_color = color;
} 