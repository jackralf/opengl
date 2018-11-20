#include "vec2.h"

vec2::vec2()
{

}

vec2::vec2(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

vec2& vec2::add(const vec2& other)
{
	this->x += other.x;
	this->y += other.y;
	
	return *this;
}

vec2& vec2::sub(const vec2& other)
{
	this->x -= other.x;
	this->y -= other.y;

	return *this;
}

vec2& vec2::mul(const vec2& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

vec2& vec2::div(const vec2& other)
{
	this->x /= other.x;
	this->y /= other.y;

	return *this;
}

vec2 vec2::operator+(const vec2& other)
{
	return vec2(x + other.x, y + other.y);
}

vec2 vec2::operator-(const vec2& other)
{
	return vec2(x - other.x, y - other.y);
}

vec2 vec2::operator*(const vec2& other)
{
	return vec2(x * other.x, y * other.y);
}

vec2 vec2::operator/(const vec2& other)
{
	return vec2(x / other.x, y / other.y);
}

vec2& vec2::operator/=(const vec2& other)
{
	return div(other);
}

float vec2::operator[](int index) const
{
	if (index == 0) {
		return x;
	}
	else if (index == 1) {
		return y;
	}

	return 0.0f;
}

vec2& vec2::operator*=(const vec2& other)
{
	return mul(other);
}

vec2& vec2::operator-=(const vec2& other)
{
	return sub(other);
}

vec2& vec2::operator+=(const vec2& other)
{
	return add(other);
}

std::ostream& operator<<(std::ostream & stream, const vec2 & vector)
{
	stream << "vec2: (" << vector.x << "," << vector.y << ")";
	return stream;
}
