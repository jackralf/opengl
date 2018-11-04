#include "Sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

Sprite::Sprite(std::string filepath)
	:m_pTexture(nullptr), m_Transform(1.0f)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	m_pVb = new VertexBuffer(vertices, sizeof(vertices));
	m_pIb = new IndexBuffer(indices, 6);

	m_pVa = new VertexArray();
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	m_pVa->addBuffer(*m_pVb, *m_pIb, layout);

	m_pTexture = new Texture(filepath);
	m_pShader = new Shader("res/shaders/Basic.shader");
	m_ContentSize = m_pTexture->getContentSize();

	m_pTexture->bind();
	m_pShader->setUniform1i("u_Texture", 0);
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
	m_pVa->bind();
	m_pShader->bind();
	m_pShader->setUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(m_Transform));
	m_pShader->setUniform4f("u_Color", m_Color.R / 255, m_Color.G / 255, m_Color.B / 255, m_Color.A / 255);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

