#pragma once
#include <iostream>
#include "Matrix4.h"
class Vector4
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float a, r, g, b;
		};
	};

	Vector4();
	Vector4(float v);
	Vector4(float x, float y, float z, float w);
	~Vector4();
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator*(const Matrix4& other) const;


};

std::ostream& operator<<(std::ostream& stream, const Vector4& other);