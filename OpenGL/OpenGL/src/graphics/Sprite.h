#pragma once

#include "defines.h"
#include "Renderable.h"

class Sprite : public Renderable
{
public:
	Sprite(String filepath);
    Sprite(Texture* texture);
	~Sprite();

	void setPosition(float x, float y);
	void setScale(float scale);
	void setRotation(float angle);
	void setColor(vec4 color) { m_Color = color; }
	mat4 getTransform() { return m_Transform; }

private:
	String m_FilePath;
};
