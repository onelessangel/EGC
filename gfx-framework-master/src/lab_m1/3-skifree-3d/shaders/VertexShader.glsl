#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform bool is_terrain;
uniform vec2 translation;

// Output
out vec2 texcoord;
//out vec3 position;
out vec3 world_position;
out vec3 world_normal;

void main()
{
	// Pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;

	float y = texcoord.y;
	float x = texcoord.x;

	if (is_terrain) {
		texcoord = vec2(x + translation.x / 50, y + translation.y / 50);
	}

	//position = v_position;
	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize(mat3(Model) * normalize(v_normal));

	mat4 ModelView = View * Model;
	gl_Position = Projection * ModelView * vec4(v_position, 1.f);
}