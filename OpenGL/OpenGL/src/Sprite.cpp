#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"

Sprite::Sprite(std::string filepath)
	:m_Texture(nullptr)
{
	m_Texture = new Texture(filepath);

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
	m_Transform = glm::rotate(m_Transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Sprite::draw()
{

}

