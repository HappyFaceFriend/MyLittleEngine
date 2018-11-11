#pragma once
#include "glm/glm.hpp"
#include <iostream>
class Vector2
{
public:
	float x;
	float y;
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator*(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
	Vector2 operator*(float f);
	Vector2& operator*=(float f);
	glm::vec2 GetGLMVec2();
};

std::ostream& operator<<(const std::ostream&, const Vector2& other);
Vector2& operator*(float f, const Vector2& other);
