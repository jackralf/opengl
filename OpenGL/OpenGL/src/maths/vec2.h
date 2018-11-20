#pragma once

#include <iostream>

struct vec2
{
	float x, y;

	vec2();
	vec2(const float& x, const float& y);

	vec2& add(const vec2& other);
	vec2& sub(const vec2& other);
	vec2& mul(const vec2& other);
	vec2& div(const vec2& other);

	vec2 operator+(const vec2& other);
	vec2 operator-(const vec2& other);
	vec2 operator*(const vec2& other);
	vec2 operator/(const vec2& other);

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(const vec2& other);
	vec2& operator/=(const vec2& other);

	float operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);

};