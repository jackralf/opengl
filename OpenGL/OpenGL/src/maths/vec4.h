#pragma once

#include <iostream>

struct vec4
{
	float x, y, z, w;

	vec4();
	vec4(const float& x, const float& y, const float& z, const float& w);

	vec4& add(const vec4& other);
	vec4& sub(const vec4& other);
	vec4& mul(const vec4& other);
	vec4& div(const vec4& other);

	vec4 operator+(const vec4& other);
	vec4 operator-(const vec4& other);
	vec4 operator*(const vec4& other);
	vec4 operator/(const vec4& other);

	vec4& operator+=(const vec4& other);
	vec4& operator-=(const vec4& other);
	vec4& operator*=(const vec4& other);
	vec4& operator/=(const vec4& other);

	float operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);

};