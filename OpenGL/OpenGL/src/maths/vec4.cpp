#include "vec4.h"

vec4::vec4()
{

}

vec4::vec4(const float& x, const float& y, const float& z, const float& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4& vec4::add(const vec4& other)
{
	this->x += other.x;
	this->y += other.y;
	this->x += other.z;
	this->w += other.w;

	return *this;
}

vec4& vec4::sub(const vec4& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	this->w -= other.w;

	return *this;
}

vec4& vec4::mul(const vec4& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->y *= other.z;
	this->w *= other.w;

	return *this;
}

vec4& vec4::div(const vec4& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
	this->w /= other.w;

	return *this;
}

vec4 vec4::operator+(const vec4& other)
{
	return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

vec4 vec4::operator-(const vec4& other)
{
	return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

vec4 vec4::operator*(const vec4& other)
{
	return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

vec4 vec4::operator/(const vec4& other)
{
	return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
}

vec4& vec4::operator/=(const vec4& other)
{
	return div(other);
}

float vec4::operator[](int index) const
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
	else if (index == 3) {
		return w;
	}

	return 0.0f;
}

vec4& vec4::operator*=(const vec4& other)
{
	return mul(other);
}

vec4& vec4::operator-=(const vec4& other)
{
	return sub(other);
}

vec4& vec4::operator+=(const vec4& other)
{
	return add(other);
}

std::ostream& operator<<(std::ostream & stream, const vec4 & vector)
{
	stream << "vec4: (" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ")";
	return stream;
}
