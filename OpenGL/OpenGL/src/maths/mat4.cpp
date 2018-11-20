#include "mat4.h"
#include "maths_fun.h"

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

	memcpy(elements, data, 4 * 4 * sizeof(float));

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
	mat4 result(1.0f);

	float r = toRadian(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	result.elements[0 + 0 * 4] = c + omc * x * x;
	result.elements[1 + 0 * 4] = omc * y * x + s * z;
	result.elements[2 + 0 * 4] = omc * z * x - s * y;

	result.elements[0 + 1 * 4] = omc * x * y - s * z;
	result.elements[1 + 1 * 4] = c + omc * y * y;
	result.elements[2 + 1 * 4] = omc * z * y + s * x;

	result.elements[0 + 2 * 4] = omc * x * z + s * y;
	result.elements[1 + 2 * 4] = omc * y * z - s * x;
	result.elements[2 + 2 * 4] = c + omc * z * z;

	return result;
}

mat4 mat4::scale(const vec3& scale)
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = scale.x;
	result.elements[1 + 1 * 4] = scale.y;
	result.elements[2 + 2 * 4] = scale.z;

	return result;
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 result(1.0f);

	result.elements[0 + 0 * 4] = 2.0f / (right - left);
	result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	result.elements[2 + 2 * 4] = -2.0f / (far - near);
	
	result.elements[0 + 3 * 4] = -1.0f * (right + left) / (right - left);
	result.elements[1 + 3 * 4] = -1.0f * (top + bottom) / (top - bottom);
	result.elements[2 + 3 * 4] = -1.0f * (far + near) / (far - near);

	return result;
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	mat4 result(1.0f);

	float q = 1.0f / tan(toRadian(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[2 + 3 * 4] = -1.0f;
	result.elements[3 + 2 * 4] = c;

	return result;
}

std::ostream& operator<<(std::ostream& stream, const mat4& matric)
{
	stream << "mat4:" << std::endl
		<< matric.elements[0] << ", " << matric.elements[4] << ", " << matric.elements[8] << ", " << matric.elements[12] << std::endl
		<< matric.elements[1] << ", " << matric.elements[5] << ", " << matric.elements[9] << ", " << matric.elements[13] << std::endl
		<< matric.elements[2] << ", " << matric.elements[6] << ", " << matric.elements[10] << ", " << matric.elements[14] << std::endl
		<< matric.elements[3] << ", " << matric.elements[7] << ", " << matric.elements[11] << ", " << matric.elements[15] << std::endl;

	return stream;
}