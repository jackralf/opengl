#pragma once

#include "Renderer.h"
#include <vector>

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_COLOR_INDEX		2

#define VERTEX_DATA_SIZE   sizeof(VertexData)

#define MAX_SPRITES			60000
#define SPRITE_SIZE			VERTEX_DATA_SIZE * 4
#define MAX_BUFFER_SIZE		MAX_SPRITES * SPRITE_SIZE
#define MAX_INDICES_SIZE    MAX_SPRITES * 6

class Texture;
class IndexBuffer;
class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void init();
	void begin();
	void submit(const Renderable* renderable) override;
	void end();

	void flush() override;
private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	IndexBuffer* m_IBO;
    const Texture* m_Texture;

	VertexData* m_Buffer;
	int m_IndexCount;
};
