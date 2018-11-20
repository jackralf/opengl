#include "SpriteRenderer.h"
#include "Sprite.h"

#include "defines.h"
#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

SpriteRenderer::SpriteRenderer()
{

}

SpriteRenderer::~SpriteRenderer()
{

}

void SpriteRenderer::setup()
{

}

void SpriteRenderer::draw()
{
	for (unsigned int i = 0; i < m_SpriteInfoList.size(); i++) {
		auto spriteInfo = m_SpriteInfoList[i];

		mat4 transform = spriteInfo->transform;
		auto textureId = spriteInfo->textureId;
		//TODO
		GLfloat vertices[4 * 5];
		unsigned int len = sizeof(spriteInfo->vertices) / sizeof(spriteInfo->vertices[0]);
		for (unsigned int j = 0; j < len; j++) {
			for (unsigned int k = 0; k < 5; k++) {
				if (k < 3)
					vertices[j * 5 + k] = spriteInfo->vertices[j][k];
				else
					vertices[j * 5 + k] = spriteInfo->uvCoords[j][k - 3];
			}
		}

		const unsigned int* indices = &(spriteInfo->indices[0]);

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, 24);

		VertexArray va;
		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, ib, layout);

		mat4 view(1.0f);
		view = mat4::translate(vec3(0.0f, 0.0f, -101.0f));

		std::cout << transform << std::endl;
		std::cout << view << std::endl;
		std::cout << view * transform << std::endl;

		mat4 projection;
		projection = mat4::orthographic(0, 960, 0, 640, 0, 100);


		Shader shader("res/shaders/Basic.shader");
		shader.setUniform1i("u_Texture", 0);
		shader.bind();
		shader.setUniformMatrix4fv("MVP", 1, GL_FALSE, (projection * transform).elements);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

