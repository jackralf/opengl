#pragma once

#include "vec3.h"
#include "vec4.h"
#include <iostream>

struct mat4
{
	union {
		float elements[16];
		vec4 columns[4];
	};

	mat4();
	mat4(const mat4& other);
	mat4(float diagonal);

	static mat4 identity();

	mat4& multiply(const mat4& other);
	mat4 operator*(const mat4& other);

	static mat4 translate(const vec3& translation);
	static mat4 rotate(float angle, const vec3& axis);
	static mat4 scale(const vec3& scale);

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	friend std::ostream& operator<<(std::ostream& stream, const mat4& matric);

};