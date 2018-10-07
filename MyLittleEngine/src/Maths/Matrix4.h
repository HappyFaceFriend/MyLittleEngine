#pragma once
#include <iostream>
#include <array>
#include "Vector4.h"
class Matrix4
{
private:
	std::array<float, 16> m_Array;
public:
	static const Matrix4 identity;
	Matrix4();
	Matrix4(float *datas);
	Matrix4(const std::array<float, 16>& datas);
	Matrix4(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10,
		float d11, float d12, float d13, float d14, float d15);
	~Matrix4();
	void Set(float *datas);
	void Set(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10,
		float d11, float d12, float d13, float d14, float d15);
	void Set(const std::array<float, 16>& datas);
	void SetRow(int row, float *datas);
	void SetColumn(int column, float *datas);
	void SetIdentity();
	std::array<float, 16> GetStdArray() const;
	const float* GetArray() const;
	Matrix4 operator+(const Matrix4& other) const;
	Matrix4 operator-(const Matrix4& other) const;
	Matrix4 operator*(const Matrix4& other) const;
	Vector4 operator*(const Vector4& other) const;

	static Matrix4 TranslateMat(float x, float y, float z);
	static Matrix4 TranslateMat(float v);
	static Matrix4 ScaleMat(float x, float y, float z);
	static Matrix4 ScaleMat(float v);
};

std::ostream& operator<<(std::ostream& stream, const Matrix4& mat);