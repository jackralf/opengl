#include "Sprite.h"

#include "Texture.h"
#include "SpriteRenderer.h"

Sprite::Sprite(std::string filepath)
	:m_pTexture(nullptr), m_Transform(1.0f)
{
	m_pTexture = new Texture(filepath);
	m_SpriteInfo.textureId = m_pTexture->getTextureId();
	m_SpriteInfo.transform = mat4(1);

	auto size = m_pTexture->getContentSize();

	vec3 BL = vec3(0,0,0);
	vec3 BR = vec3(size.width, 0, 0);
	vec3 TR = vec3(size.width, size.height, 0);
	vec3 TL = vec3(0, size.height, 0);
	m_SpriteInfo.vertices[0] = BL;
	m_SpriteInfo.vertices[1] = BR;
	m_SpriteInfo.vertices[2] = TR;
	m_SpriteInfo.vertices[3] = TL;
	m_SpriteInfo.uvCoords[0] = vec2(0, 0);
	m_SpriteInfo.uvCoords[1] = vec2(1, 0);
	m_SpriteInfo.uvCoords[2] = vec2(1, 1);
	m_SpriteInfo.uvCoords[3] = vec2(0, 1);

	m_SpriteInfo.indices[0] = 0;
	m_SpriteInfo.indices[1] = 1;
	m_SpriteInfo.indices[2] = 2;
	m_SpriteInfo.indices[3] = 2;
	m_SpriteInfo.indices[4] = 3;
	m_SpriteInfo.indices[5] = 0;
}

Sprite::~Sprite()
{

}

void Sprite::setPosition(float x, float y)
{
	m_Transform = mat4::translate(vec3(x, y, 0.0f));
}

void Sprite::setScale(float scale)
{
	m_Transform = mat4::scale(vec3(scale, scale, 1.0f));
}

void Sprite::setRotation(float angle)
{
	m_Transform = mat4::rotate(-angle, vec3(0.0f, 0.0f, 1.0f));
}

void Sprite::draw()
{
	SpriteRenderer::getInstance()->add(&m_SpriteInfo);
}

