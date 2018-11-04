#pragma once

#include <string>
#include <glm/glm.hpp>
#include "Texture.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;

struct Color {
	float R;
	float G;
	float B;
	float A;

	Color(float r, float g, float b)
		:R(r),G(g),B(b),A(255) {}
};

class Sprite
{
public:
	Sprite(std::string filepath);
	~Sprite();

	void setPosition(float x, float y);
	void setScale(float scale);
	void setRotation(float angle);
	void setColor(Color color) { m_Color = color; };
	glm::mat4 getTransform() { return m_Transform; }

	void draw();
private:
	std::string m_FilePath;
	glm::mat4 m_Transform;
	Texture* m_pTexture;
	Color m_Color{255,255,255};

	Shader* m_pShader;
	Size m_ContentSize;
	VertexBuffer* m_pVb;
	IndexBuffer* m_pIb;
	VertexArray* m_pVa;
};