#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_RendererId);
}

void VertexArray::unBind() const
{
	glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout)
{
	bind();
	vb.bind();
	ib.bind();

	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count *  VertexBufferElement::getSizeOfType(element.type);
	}

}

