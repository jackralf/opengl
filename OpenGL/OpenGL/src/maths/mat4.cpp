#include "mat4.h"


mat4::mat4()
{
	memset(elements, 0, 4 * 4 * sizeof(float));
}

mat4::mat4(float diagonal)
{
	memset(elements, 0, 4 * 4 * sizeof(float));
	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

mat4::mat4(const mat4& other)
{
	memcpy(elements, &other.elements, 4 * 4 * sizeof(float));
}

mat4 mat4::identity()
{
	return mat4(1.0f);
}

mat4& mat4::multiply(const mat4& other)
{
	float data[16];
	for (int i = 0; i < 4; i ++) {
		for (int j = 0; j < 4; j ++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += elements[i + k * 4] * other.elements[k + j * 4];
			}
			data[i + 4 * j] = sum;
		}
	}

	memset(elements, 0, 4 * 4 * sizeof(float));

	return *this;
}

mat4 mat4::operator*(const mat4& other)
{
	mat4 self(*this);
	return self.multiply(other);
}

mat4 mat4::translate(const vec3& translation)
{
	mat4 result(1.0f);
	result.elements[0 + 3 * 4] = translation.x;
	result.elements[1 + 3 * 4] = translation.y;
	result.elements[2 + 3 * 4] = translation.z;

	return result;
}

mat4 mat4::rotate(float angle, const vec3& axis)
{
	
}

mat4 mat4::scale(const vec3& scale)
{

}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{

}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{

}

