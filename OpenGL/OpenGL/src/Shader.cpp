#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
	:m_FilePath(filepath)
{
	ShaderProgramSource source = parseShader(filepath);
	m_RendererId = createShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader()
{

}

void Shader::bind()
{
	glUseProgram(m_RendererId);
}

void Shader::unbind()
{
	glDeleteProgram(m_RendererId);
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::createShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	GLuint program = glCreateProgram();
	GLuint vertexShader, fragmentShader;

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

unsigned int Shader::compileShader(GLenum type, const std::string& source)
{
	GLuint shader = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint status;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return 0;
	}

	return shader;
}

int Shader::getUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_RendererId,  name.c_str());
	return location;
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
	glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniformMatrix4fv(const std::string& name, unsigned int count, bool transpose, const float* value)
{
	glUniformMatrix4fv(getUniformLocation(name), count, transpose, value);
}
