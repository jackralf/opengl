#pragma once

#include <iostream>

struct vec3
{
	float x, y, z;

	vec3();
	vec3(const float& x, const float& y, const float& z);

	vec3& add(const vec3& other);
	vec3& sub(const vec3& other);
	vec3& mul(const vec3& other);
	vec3& div(const vec3& other);

	vec3 operator+(const vec3& other);
	vec3 operator-(const vec3& other);
	vec3 operator*(const vec3& other);
	vec3 operator/(const vec3& other);

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(const vec3& other);
	vec3& operator/=(const vec3& other);

	float operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);

};