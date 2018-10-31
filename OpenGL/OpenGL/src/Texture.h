#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string filepath);
	~Texture();

	void bind(int slot = 0);
	void unbind();

private:
	unsigned int m_RendererId;
	int m_Width, m_height, m_bpp;
	unsigned char* m_bufferData;
	std::string m_filePath;
};