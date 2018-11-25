#include "Window.h"

#include <iostream>

#include "Sprite.h"
#include "Shader.h"
#include "SpriteRenderer.h"
#include <math.h>
#include "Texture.h"


int main(void)
{
	Window window("hello", 960, 640);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

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


	Texture texture("res/image/icon.png");
	texture.bind();

	SpriteRenderer render;

	unsigned int frame = 0;
	double lastTime = glfwGetTime();
	while (!window.closed())
	{		
		window.clear();

		float x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos",  x / 960 - 0.5, (640.0f - y) / 640 - 0.5);

		render.begin();
		
		for (auto sp : spriteList) {
			render.submit(sp);
		}

		render.end();

		render.flush();


		frame++;
		double currentTime = glfwGetTime();
		if (currentTime - lastTime >= 1.0) {
			std::cout << "fps:" << frame << std::endl;
			frame = 0;
			lastTime += 1.0;
		}

		window.update();
	}

	return 0;
}

