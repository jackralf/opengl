#pragma once

class VertexBuffer 
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void unbind();

private:
	unsigned int m_RendererID;
};