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
		auto& spriteInfo = m_SpriteInfoList[i];

		mat4 transform = spriteInfo->transform;
		auto textureId = spriteInfo->textureId;
		//TODO
		const float* vertices = &(spriteInfo->pointInfo->vertices.x);
		const unsigned int* indices = &(spriteInfo->indices[0]);
		/*auto vertices = spriteInfo.vertices;
		auto uvCoords = spriteInfo.uvCoords;*/


	/*	GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};*/

		//GLuint indices[] = {
		//	0, 1, 2,
		//	2, 3, 0
		//};


		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		VertexBuffer vb(vertices, sizeof(vertices));
		IndexBuffer ib(indices, sizeof(indices));

		VertexArray va;
		VertexBufferLayout layout;
		layout.push<float>(3);
		layout.push<float>(2);
		va.addBuffer(vb, ib, layout);

		glm::mat4 view(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), float(640.0 / 640), 0.1f, 100.f);


		Shader shader("res/shaders/Basic.shader");
		shader.setUniform1i("u_Texture", 0);
		shader.bind();
		shader.setUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(projection * view * transform));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

