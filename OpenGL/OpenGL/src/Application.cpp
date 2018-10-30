#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace std;

GLuint createProgram();
bool compileShader(GLenum type, GLuint *shader, const GLchar *source);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << action << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	GLfloat vertices[] = {
		-0.5f, 0.0f, 0.0f,
		 0.0f, -1.0f, 0.0f,
		 1.0f, 0.0f, 0.0f,
		 0.0f, 0.5f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 2, 
		2, 3, 0
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	vb.Bind();

	IndexBuffer eb(indices, 6);
	eb.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint progrom = createProgram();
	glUseProgram(progrom);

	GLint location = glGetUniformLocation(progrom, "u_Color");
	glUniform4f(location, 0.8f, 0.2f, 0.3f, 1.0f);

	GLfloat model[] = {
		0.5f, 0.0, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	GLint modelLoc = glGetUniformLocation(progrom, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model);


	GLfloat view[] = {
		1.0f, 0.0, 0.0f, 0.5f,
		0.0f, 1.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	GLint viewLoc = glGetUniformLocation(progrom, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		


		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

struct ShaderProgramSource
{
	string vertexSource;
	string fragmentSource;
};

static ShaderProgramSource parseShader(const string& filePath)
{
	ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != string::npos)
				type = ShaderType::FRAGMENT;
		} 
		else {
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}


GLuint createProgram()
{
	GLuint program = glCreateProgram();
	GLuint vertexShader, fragmentShader;

	ShaderProgramSource source = parseShader("res/shaders/Basic.shader");
	compileShader(GL_VERTEX_SHADER, &vertexShader, source.vertexSource.c_str());
	compileShader(GL_FRAGMENT_SHADER, &fragmentShader, source.fragmentSource.c_str());

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

bool compileShader(GLenum type, GLuint *shader, const GLchar *source)
{
	if (shader == NULL)
		return false;

	*shader = glCreateShader(type);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);

	GLint status;
	GLchar infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	return (status == GL_TRUE);
}