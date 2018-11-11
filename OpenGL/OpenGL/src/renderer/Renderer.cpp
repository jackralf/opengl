#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

Renderer* Renderer::m_Instance = nullptr;
Renderer::Renderer()
	:m_Projection(1.0f)
{

}

Renderer::~Renderer()
{

}

void Renderer::draw(VertexBuffer& vb, IndexBuffer& ib, Shader& shader)
{
	vb.bind();
	ib.bind();
	shader.bind();

	
	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
