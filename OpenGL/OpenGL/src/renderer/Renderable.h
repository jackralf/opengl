#pragma once

#include "defines.h"
#include "Texture.h"

struct VertexData
{
	vec3 vertex;
	vec2 texCoord;
	unsigned int color;
};

class Renderable
{
public:
	Renderable()
		:m_Position(vec3(0,0,0)), m_Color(vec4(1.0f, 1.0f, 0.0f, 1.0f)), m_Texture(nullptr)
	{};
	Renderable(vec3 position, Size size, vec4 color)
		:m_Position(position), m_Size(size), m_Color(color)
	{}

	inline const vec3& getPosition() const { return m_Position; }
	inline const vec4& getColor() const { return m_Color; }
	inline const Size& getSize() const { return m_Size; }
	inline const Texture* getTexture() const { return m_Texture; }
	inline const mat4& getTransform() const { return m_Transform; }

protected:
	vec3 m_Position;
	vec4 m_Color;
	Size m_Size;
	mat4 m_Transform;

	Texture* m_Texture;
};