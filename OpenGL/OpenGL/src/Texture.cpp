#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"

Texture::Texture(const std::string filepath)
	:m_Width(0), m_height(0), m_filePath(filepath), m_bpp(0), m_bufferData(nullptr)
{
	glGenTextures(1, &m_RendererId);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);

	m_bufferData = stbi_load(filepath.c_str(), &m_Width, &m_height, &m_bpp, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_bufferData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererId);
}

void Texture::bind(int slot /*= 0*/)
{
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

