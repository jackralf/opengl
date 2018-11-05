#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "RendererCommand.h"
#include <vector>

class VertexBuffer;
class IndexBuffer;
class Shader;
class Renderer
{
public:

	static Renderer* getInstance() {
		if (!m_Instance) {
			m_Instance = new Renderer();
		}
		return m_Instance;
	}
	
	Renderer();
	~Renderer();

	virtual void draw(VertexBuffer& vb, IndexBuffer& ib, Shader& shader);
	void clear();

	void addCommand(RendererCommand& command) { m_CommandList.push_back(command); };

	glm::mat4 getProjectionMatrix() { return m_Projection; };
private:
	
	glm::mat4 m_Projection;
	std::vector<RendererCommand> m_CommandList;
	static Renderer* m_Instance;
};