#shader vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
uniform mat4 model;
uniform mat4 view;

out vec2 TexCoord;

void main()
{
	gl_Position = view * model * vec4(position.x, position.y, position.z, 1.0);
	TexCoord = texCoord;
}



#shader fragment
#version 330 core

in vec2 TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	gl_FragColor = texture(u_Texture, TexCoord) * u_Color;
}