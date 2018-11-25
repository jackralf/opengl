#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unBind() const;

	void addBuffer(const VertexBuffer& vb, const IndexBuffer& ib, const VertexBufferLayout& layout);

private:
	unsigned int m_RendererId;
};