#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec4 color;

uniform mat4 MVP;

out vec2 TexCoord;
out vec4 Color;
out vec4 Position;

void main()
{
	gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
	TexCoord = texCoord;
	Color = color;
	Position = gl_Position;
}



#shader fragment
#version 330 core

in vec2 TexCoord;
in vec4 Color;
in vec4 Position;

uniform vec2 light_pos;
uniform sampler2D u_Texture;

void main()
{
	float intensity = 1.0 / length(Position.xy - light_pos);
	gl_FragColor = texture(u_Texture, TexCoord) * Color * intensity;
}