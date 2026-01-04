#version 460 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform bool useTexture;

void main()
{
	if	(useTexture)
		FragColor = texture(texture1, TexCoord);
	else
		FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}