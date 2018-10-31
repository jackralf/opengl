#pragma once

#include <GL/glew.h>

class VertexBuffer;
class IndexBuffer;
class Renderer
{
public:
	void draw(VertexBuffer& vb, IndexBuffer& ib);
	void clear();
private:
	
};