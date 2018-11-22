#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

uniform mat4 MVP;

out vec2 TexCoord;
out vec4 Color;

void main()
{
	gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
	TexCoord = texCoord;
	Color = color;
}



#shader fragment
#version 330 core

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D u_Texture;

void main()
{
	gl_FragColor = texture(u_Texture, TexCoord) * Color;
}