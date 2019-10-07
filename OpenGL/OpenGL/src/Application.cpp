#include "Window.h"

#include <iostream>

#include "Sprite.h"
#include "Shader.h"
#include "SpriteRenderer.h"
#include <math.h>
#include "Texture.h"
#include "RenderTexture.h"

int main(void)
{
    int width = 960, height = 640;
	Window window("hello", width, height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	std::vector<Sprite*> spriteList;
	for (int x = 0; x < 900; x += 100.f) {
		for (int y = 0; y < 600; y += 100.f) {
			auto sp = new Sprite("res/image/icon.png");
			sp->setPosition(x, y);
			sp->setColor(vec4(x / 960.0f, y / 640.0f, (x + y)/ (960.0f + 640.0f), 1.0f));
			spriteList.push_back(sp);
		}
	}

	//Renderer renderer;
	Shader shader("res/shaders/Basic.shader");
	shader.bind();
	
	mat4 projection = mat4::orthographic(0, width, 0, height, 0, 1000);
	mat4 model(1.0f);
	shader.setUniform1i("u_Texture", 0);
	shader.setUniformMatrix4fv("MVP", 1, GL_FALSE, (projection * model).elements);

	SpriteRenderer render;
    
    RenderTexture rt(width, height);
    bool first = true;
    
    
	unsigned int frame = 0;
	double lastTime = glfwGetTime();
	while (!window.closed())
	{		
		window.clear();
        
		float x, y;
		window.getMousePosition(x, y);
        shader.setUniform2f("light_pos",  x / 480 - 1.0, (640.0f - y) / 320 - 1.0);

        glViewport(0, 0, 960, 640);
        render.begin();

        for (auto sp : spriteList) {
            render.submit(sp);
        }

        render.end();

        render.flush();
        
//        glViewport(50, 400, 200, 200);
//        render.begin();
//
//        for (auto sp : spriteList) {
//            render.submit(sp);
//        }
//
//        render.end();
//
//        render.flush();
        
        if(first) {
            rt.begin();
            
            shader.bind();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            render.begin();
            for (auto sp : spriteList) {
                render.submit(sp);
            }
            render.end();
            render.flush();
            
            rt.end();
            rt.saveToFile("res/image/hello.png");
            first = false;
        }
        

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

