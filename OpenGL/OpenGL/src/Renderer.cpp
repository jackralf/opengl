#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

void Renderer::draw(VertexBuffer& vb, IndexBuffer& ib)
{
	vb.bind();
	ib.bind();


}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

