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

Vector4 Vector4::operator*(const Matrix4& other) const
{
	Vector4 result;
	const float *arr = other.GetArray();
	result.x = x*arr[0] + y*arr[1] + z*arr[2] + w*arr[3];
	result.y = x*arr[4] + y*arr[5] + z*arr[6] + w*arr[7];
	result.z = x*arr[8] + y*arr[9] + z*arr[10] + w*arr[11];
	result.w = x*arr[12] + y*arr[13] + z*arr[14] + w*arr[15];
	return result;
}

std::ostream& operator<<(std::ostream& stream, const Vector4& other)
{
	stream << '(' << other.x << ',' << other.y << ',' << other.z << ',' << other.w << ')';
	return stream;
}
