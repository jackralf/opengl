#include "Sprite.h"

#include "Texture.h"
#include "SpriteRenderer.h"

Sprite::Sprite(std::string filepath)
	:m_pTexture(nullptr), m_Transform(1.0f)
{
	m_pTexture = new Texture(filepath);
	m_SpriteInfo.textureId = m_pTexture->getTextureId();
	m_SpriteInfo.transform = mat4(1);

	auto size = Size{1,1};

	vec3 BL = vec3(0,0,0);
	vec3 BR = vec3(size.width, 0, 0);
	vec3 TR = vec3(size.width, size.height, 0);
	vec3 TL = vec3(0, size.height, 0);
	m_SpriteInfo.pointInfo[0] = { BL, vec2(0, 0) };
	m_SpriteInfo.pointInfo[1] = { BR, vec2(1, 0) };
	m_SpriteInfo.pointInfo[2] = { TR, vec2(1, 1) };
	m_SpriteInfo.pointInfo[3] = { TL, vec2(0, 1) };

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
	m_Transform = glm::translate(m_Transform, glm::vec3(x, y, 0.0f));
}

void Sprite::setScale(float scale)
{
	m_Transform = glm::scale(m_Transform, glm::vec3(scale, scale, 1.0f));
}

void Sprite::setRotation(float angle)
{
	m_Transform = glm::rotate(m_Transform, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Sprite::draw()
{
	SpriteRenderer::getInstance()->add(&m_SpriteInfo);
}

