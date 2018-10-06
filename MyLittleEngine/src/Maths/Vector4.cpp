#include "Vector4.h"



Vector4::Vector4():x(0), y(0), z(0), w(1)
{	
}

Vector4::Vector4(float v) : x(v), y(v), z(v), w(1)
{
}
Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{
}
Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4::~Vector4()
{
}


std::ostream& operator<<(std::ostream& stream, const Vector4& other)
{
	stream << '(' << other.x << ',' << other.y << ',' << other.z << ',' << other.w << ')';
	return stream;
}
