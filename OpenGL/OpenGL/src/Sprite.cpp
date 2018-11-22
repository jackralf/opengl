#include "Sprite.h"

#include "Texture.h"
#include "SpriteRenderer.h"

Sprite::Sprite(String filepath)
{
	m_Transform = mat4(1.0f);
	//m_Texture = new Texture(filepath);
	//m_Size = m_Texture->getContentSize();
	m_Size = { 10,10 };
}

Sprite::~Sprite()
{
	m_Texture->unbind();
	delete m_Texture;
}

void Sprite::setPosition(float x, float y)
{
	m_Position = vec3(x, y, 0);
}

void Sprite::setScale(float scale)
{
	m_Transform = mat4::scale(vec3(scale, scale, 1.0f));
}

void Sprite::setRotation(float angle)
{
	m_Transform = mat4::rotate(-angle, vec3(0.0f, 0.0f, 1.0f));
}
