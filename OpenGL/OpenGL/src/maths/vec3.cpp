#include "vec3.h"

vec3::vec3()
{

}

vec3::vec3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

vec3& vec3::add(const vec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->x += other.z;

	return *this;
}

vec3& vec3::sub(const vec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

vec3& vec3::mul(const vec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->y *= other.z;

	return *this;
}

vec3& vec3::div(const vec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

vec3 vec3::operator+(const vec3& other)
{
	return vec3(x + other.x, y + other.y, z + other.z);
}

vec3 vec3::operator-(const vec3& other)
{
	return vec3(x - other.x, y - other.y, z - other.z);
}

vec3 vec3::operator*(const vec3& other)
{
	return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::operator/(const vec3& other)
{
	return vec3(x / other.x, y / other.y, z / other.z);
}

vec3& vec3::operator/=(const vec3& other)
{
	return div(other);
}

float vec3::operator[](int index) const
{
	if (index == 0) {
		return x;
	}
	else if (index == 1) {
		return y;
	}
	else if (index == 2) {
		return z;
	}

	return 0.0f;
}

vec3& vec3::operator*=(const vec3& other)
{
	return mul(other);
}

vec3& vec3::operator-=(const vec3& other)
{
	return sub(other);
}

vec3& vec3::operator+=(const vec3& other)
{
	return add(other);
}

std::ostream& operator<<(std::ostream & stream, const vec3 & vector)
{
	stream << "vec3: (" << vector.x << "," << vector.y << "," << vector.z << ")";
	return stream;
}
