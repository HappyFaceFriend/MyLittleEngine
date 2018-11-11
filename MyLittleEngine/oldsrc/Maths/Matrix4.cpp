#include "Matrix4.h"

const Matrix4 Matrix4::identity(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);

Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		m_Array[i] = 0;
}

Matrix4::Matrix4(float *datas)
{
	Set(datas);
}

Matrix4::Matrix4(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10, float d11, float d12, float d13, float d14, float d15)
{
	Set(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15);
}

Matrix4::Matrix4(const std::array<float, 16>& datas)
{
	m_Array = datas;
}


Matrix4::~Matrix4()
{
}

void Matrix4::Set(float *datas)
{
	for (int i = 0; i < 16; i++)
		m_Array[i] = datas[i];
}

void Matrix4::Set(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10, float d11, float d12, float d13, float d14, float d15)
{
	m_Array[0] = d0;
	m_Array[1] = d1;
	m_Array[2] = d2;
	m_Array[3] = d3;
	m_Array[4] = d4;
	m_Array[5] = d5;
	m_Array[6] = d6;
	m_Array[7] = d7;
	m_Array[8] = d8;
	m_Array[9] = d9;
	m_Array[10] = d10;
	m_Array[11] = d11;
	m_Array[12] = d12;
	m_Array[13] = d13;
	m_Array[14] = d14;
	m_Array[15] = d15;
}

void Matrix4::Set(const std::array<float, 16>& datas)
{
	m_Array = datas;
}

void Matrix4::SetRow(int row, float *datas)
{
	for (int i = 0; i < 4; i++)
		m_Array[row * 4 + i] = datas[i];
}

void Matrix4::SetColumn(int column, float *datas)
{
	for (int i = 0; i < 4; i++)
		m_Array[column + 4 * i] = datas[i];
}

void Matrix4::SetIdentity()
{
	Set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

std::array<float, 16> Matrix4::GetStdArray() const
{
	//TODO: c++배열 공부하기
	return m_Array;
}
const float* Matrix4::GetArray() const
{
	return m_Array.data();
}


Matrix4 Matrix4::operator+(const Matrix4 & other) const
{
	Matrix4 result(m_Array);
	for (int i = 0; i < 16; i++)
		result.m_Array[i] += other.m_Array[i];
	return result;
}

Matrix4 Matrix4::operator-(const Matrix4 & other) const
{
	Matrix4 result(m_Array);
	for (int i = 0; i < 16; i++)
		result.m_Array[i] -= other.m_Array[i];
	return result;
}

Matrix4 Matrix4::operator*(const Matrix4 & other) const
{
	Matrix4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m_Array[i * 4 + j] += m_Array[i * 4 + k] * other.m_Array[j + k * 4];
			}
		}
	}
	return result;
}

Vector4 Matrix4::operator*(const Vector4& other) const
{
	Vector4 result;
	result.x = other.x*m_Array[0] + other.y*m_Array[1] + other.z*m_Array[2] + other.w*m_Array[3];
	result.y = other.x*m_Array[4] + other.y*m_Array[5] + other.z*m_Array[6] + other.w*m_Array[7];
	result.z = other.x*m_Array[8] + other.y*m_Array[9] + other.z*m_Array[10] + other.w*m_Array[11];
	result.w = other.x*m_Array[12] + other.y*m_Array[13] + other.z*m_Array[14] + other.w*m_Array[15];
	return result;
}

Matrix4 Matrix4::TranslateMat(float x, float y, float z)
{
	return Matrix4( 1, 0, 0, x, 
					0, 1, 0, y, 
					0, 0, 1, z, 
					0, 0, 0, 1);
}
Matrix4 Matrix4::TranslateMat(float v)
{
	return Matrix4( 1, 0, 0, v,
					0, 1, 0, v,
					0, 0, 1, v,
					0, 0, 0, 1);
}
Matrix4 Matrix4::ScaleMat(float x, float y, float z)
{
	return Matrix4( x, 0, 0, 0,
					0, y, 0, 0,
					0, 0, z, 0,
					0, 0, 0, 1);
}
Matrix4 Matrix4::ScaleMat(float v)
{
	return Matrix4( v, 0, 0, 0,
					0, v, 0, 0,
					0, 0, v, 0,
					0, 0, 0, 1);
}
std::ostream& operator<<(std::ostream& stream, const Matrix4& mat)
{
	const float *arr = mat.GetArray();
	stream << '[';
	for (int i = 0; i < 4; i++)
	{
		stream << '[' << arr[i * 4];
		for (int j = 1; j <= 3; j++)
			stream << ',' << arr[i * 4 + j];
		stream << ']';
		if (i != 3)
			stream << ',';
	}

	stream << ']';
	return stream;
}