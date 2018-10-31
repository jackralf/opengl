#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind();
	void unbind();

private:
	unsigned int m_RendererID;
};