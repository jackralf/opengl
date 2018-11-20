#pragma once

#include <math.h>

#define M_PI 3.14159265358979323846

float toRadian(float degrees)
{
	return M_PI * degrees / 180.0f;
}