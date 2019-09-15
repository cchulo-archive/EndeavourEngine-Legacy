#version 330 core

in vec2 UV;

uniform sampler2D tex;

out vec4 color;

void main()
{
	vec4 texColor = texture(tex, UV);
    color = vec4(texColor.xyz, 1.f);
	
}
