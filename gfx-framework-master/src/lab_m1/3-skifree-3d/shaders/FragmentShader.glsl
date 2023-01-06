#version 330
 
uniform sampler2D texture;

uniform vec2 translation;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	//float y = texcoord.y;
	//float x = texcoord.x;

	//vec2 texcoord_2 = vec2(x + translation.x / 50, y + translation.y / 50);

	// calculate the out_color using the texture2D() function
	vec4 colour1 = texture2D(texture, texcoord);
	
	out_color = colour1;
	
	if (out_color.a < .5f)
	{
		discard;
	}
}