#include "SpriteRenderer.h"
#include "IndexBuffer.h"

SpriteRenderer::SpriteRenderer()
	:m_IndexCount(0)
{
	init();
}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::init()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_DATA_SIZE, 0);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_DATA_SIZE, (const void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_DATA_SIZE, (const void *)(5 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int* indices = new unsigned int[MAX_INDICES_SIZE];
	int offset = 0;
	for (int i = 0; i < MAX_INDICES_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	m_IBO = new IndexBuffer(indices, MAX_INDICES_SIZE);

	glBindVertexArray(0);
}

void SpriteRenderer::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	m_Buffer = (VertexData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void SpriteRenderer::submit(const Renderable* renderable)
{
	auto& position = renderable->getPosition();
	auto& size = renderable->getSize();
	auto& color = renderable->getColor();
    auto texture = renderable->getTexture();
    if(m_Texture) {
        if(m_Texture->getTextureId() != texture->getTextureId()) {
            //TODO flush
        }
    } else {
        m_Texture = texture;
    }


	int r = color.x * 255.0f;
	int g = color.y * 255.0f;
	int b = color.z * 255.0f;
	int a = color.w * 255.0f;

	unsigned int c = a << 24 | b << 16 | g << 8 | r;


	m_Buffer->vertex = position;
	m_Buffer->texCoord = vec2(0, 0);
	m_Buffer->color = c;
	m_Buffer++;

	m_Buffer->vertex = vec3(position.x + size.width, position.y, position.z);
	m_Buffer->texCoord = vec2(1, 0);
	m_Buffer->color = c;
	m_Buffer++;

	m_Buffer->vertex = vec3(position.x + size.width, position.y + size.height, position.z);
	m_Buffer->texCoord = vec2(1, 1);
	m_Buffer->color = c;
	m_Buffer++;

	m_Buffer->vertex = vec3(position.x, position.y + size.height, position.z);
	m_Buffer->texCoord = vec2(0, 1);
	m_Buffer->color = c;
	m_Buffer++;

	m_IndexCount += 6;
}

void SpriteRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteRenderer::flush()
{
	glBindVertexArray(m_VAO);
	m_IBO->bind();
    m_Texture->bind();
	
	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

	m_IBO->unbind();
	glBindVertexArray(0);
	m_IndexCount = 0;
}
