#pragma once

#include "Renderer.h"
#include <string>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void bind();
	void unbind();

	GLuint createShader(const std::string& vertexSource, const std::string& fragmentSource);
	ShaderProgramSource parseShader(const std::string& filepath);
	unsigned int compileShader(GLenum type, const std::string& source);

	int getUniformLocation(const std::string& name);
	void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void setUniformMatrix4fv(const std::string& name, unsigned int count, bool transpose, const float* value);
private:
	std::string m_FilePath;
	unsigned int m_RendererId;

};