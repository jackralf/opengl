#pragma once

#include <GL/glew.h>

class VertexBuffer;
class IndexBuffer;
class Shader;
class Renderer
{
public:
	void draw(VertexBuffer& vb, IndexBuffer& ib, Shader& shader);
	void clear();
private:
	
};