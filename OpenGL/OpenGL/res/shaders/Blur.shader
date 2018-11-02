#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
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
	vec4 sum = vec4(0.0);

	vec2 tc = TexCoord;

	float blur = 0.01f;

	float hstep = 1.0f;
	float vstep = 1.0f;

	sum += texture2D(u_Texture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
	sum += texture2D(u_Texture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
	sum += texture2D(u_Texture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
	sum += texture2D(u_Texture, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;

	sum += texture2D(u_Texture, vec2(tc.x, tc.y)) * 0.2270270270;

	sum += texture2D(u_Texture, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;
	sum += texture2D(u_Texture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
	sum += texture2D(u_Texture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
	sum += texture2D(u_Texture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;



	gl_FragColor = vec4(sum.rgba);
}