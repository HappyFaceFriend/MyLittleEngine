#include "Vector2.h"


Vector2::Vector2()
{
	x = 0;
	y = 0;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2::~Vector2()
{}

Vector2 Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}
Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
Vector2 Vector2::operator*(const Vector2& other)
{
	return Vector2(x * other.x, y * other.y);
}
Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}
Vector2 Vector2::operator*(float f)
{
	return Vector2(x*f, y*f);
}
Vector2& Vector2::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}
glm::vec2 Vector2::GetGLMVec2()
{
	return  glm::vec2(x, y);
}

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << "(" << other.x << "," << other.y << ")";
	return stream;
}
Vector2& operator*(float f, const Vector2& other)
{
	return Vector2(f*other.x, f*other.y);
}
