#pragma once

#include "Renderable.h"
#include <GL/glew.h>

class Renderer
{
public:
	virtual void submit(const Renderable* renderable) = 0;
	virtual void flush() = 0;
};