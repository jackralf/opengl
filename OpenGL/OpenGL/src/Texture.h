#pragma once

#include "defines.h"

class Texture
{
public:
	Texture(const std::string filepath);
	~Texture();

	void bind(int slot = 0) const;
	void unbind() const;

	int getWidth() const { return m_Width; }
	int getHeight() const { return m_height; }
	Size getContentSize() const { return { m_Width, m_height }; }
	unsigned int getTextureId() const { return m_RendererId; }

private:
	unsigned int m_RendererId;
	int m_Width, m_height, m_bpp;
	unsigned char* m_bufferData;
	std::string m_filePath;
};