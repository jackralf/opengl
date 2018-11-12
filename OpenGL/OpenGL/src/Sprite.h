#pragma once

#include "defines.h"
#include "Texture.h"

struct Color {
	float R;
	float G;
	float B;
	float A;

	Color(float r, float g, float b)
		:R(r),G(g),B(b),A(255) {}
};

struct SpriteInfo {
	mat4 transform;
	uint32 textureId;
	vec3 vertices[4];
	vec2 uvCoords[4];
	unsigned int indices[6];
};

class Sprite
{
public:
	Sprite(String filepath);
	~Sprite();

	void setPosition(float x, float y);
	void setScale(float scale);
	void setRotation(float angle);
	void setColor(Color color) { m_Color = color; };
	mat4 getTransform() { return m_Transform; }

	void draw();
private:
	String m_FilePath;
	SpriteInfo m_SpriteInfo;


	mat4 m_Transform;
	Texture* m_pTexture;
	Color m_Color{255,255,255};

	Size m_ContentSize;

};