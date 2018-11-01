#pragma once

#include <string>
#include <glm/glm.hpp>

class Sprite
{
public:
	Sprite(std::string filepath);
	~Sprite();

	void setPosition(float x, float y);
	void setScale(float scale);
	void setRotation(float angle);
	glm::mat4 getTransform() { return m_Transform; }
private:
	std::string m_FilePath;
	glm::mat4 m_Transform;
};