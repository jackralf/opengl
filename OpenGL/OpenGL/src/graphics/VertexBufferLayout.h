#pragma once

#include <vector>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
			
			return 0;
		}
        
        return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() :m_stride(0) {};

	template<typename T>
	void push(unsigned int count) {
	}
    
	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_stride;
};

template<>
void VertexBufferLayout::push<float>(unsigned int count) {
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
    m_stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}
