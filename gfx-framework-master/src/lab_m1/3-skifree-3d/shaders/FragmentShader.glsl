#version 330
 
uniform sampler2D texture_1;
// uniform sampler2D texture_2;
// uniform bool mix_textures;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// calculate the out_color using the texture2D() function
	vec4 colour1 = texture2D(texture_1, texcoord);
	
	out_color = colour1;
	
	if (out_color.a < .5f)
	{
		discard;
	}
}