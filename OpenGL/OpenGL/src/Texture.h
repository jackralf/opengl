#pragma once

#include <string>

struct Size{
	int width;
	int height;
};

class Texture
{
public:
	Texture(const std::string filepath);
	~Texture();

	void bind(int slot = 0);
	void unbind();

	int getWidth() { return m_Width; }
	int getHeight() { return m_height; }
	Size getContentSize() { return { m_Width, m_height }; }
	unsigned int getTextureId() { return m_RendererId; }

private:
	unsigned int m_RendererId;
	int m_Width, m_height, m_bpp;
	unsigned char* m_bufferData;
	std::string m_filePath;
};