#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include "Sprite.h"
#include "Shader.h"
#include "SpriteRenderer.h"
#include <math.h>
#include "Texture.h"


using namespace std;

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
	window = glfwCreateWindow(960, 640, "Hello World", NULL, NULL);
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

	Texture texture("res/image/icon.png");
	texture.bind();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	std::vector<Sprite*> spriteList;
	for (int x = 0; x < 960; x += 10.f) {
		for (int y = 0; y < 640; y += 10.f) {
			auto sp = new Sprite("res/image/icon.png");
			sp->setPosition(x, y);
			sp->setColor(vec4(x / 960.0f, y / 640.0f, (x + y)/ (960.0f + 640.0f), 1.0f));
			spriteList.push_back(sp);
		}
	}

	//Renderer renderer;
	Shader shader("res/shaders/Basic.shader");
	shader.bind();
	
	mat4 projection = mat4::orthographic(0, 960, 0, 640, 0, 1000);
	mat4 model(1.0f);
	shader.setUniform1i("u_Texture", 0);
	shader.setUniformMatrix4fv("MVP", 1, GL_FALSE, (projection * model).elements);

	
	SpriteRenderer render;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		render.begin();
		
		for (auto sp : spriteList) {
			render.submit(sp);
		}

		render.end();

		render.flush();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

