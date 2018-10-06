#include "Matrix4.h"



Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
		m_MatArray[i] = 0;
}

Matrix4::Matrix4(float *datas)
{
	Set(datas);
}

Matrix4::Matrix4(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10, float d11, float d12, float d13, float d14, float d15)
{
	Set(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15);
}


Matrix4::~Matrix4()
{
}

void Matrix4::Set(float *datas)
{
	for (int i = 0; i < 16; i++)
		m_MatArray[i] = datas[i];
}

void Matrix4::Set(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10, float d11, float d12, float d13, float d14, float d15)
{
	m_MatArray[0] = d0;
	m_MatArray[1] = d1;
	m_MatArray[2] = d2;
	m_MatArray[3] = d3;
	m_MatArray[4] = d4;
	m_MatArray[5] = d5;
	m_MatArray[6] = d6;
	m_MatArray[7] = d7;
	m_MatArray[8] = d8;
	m_MatArray[9] = d9;
	m_MatArray[10] = d10;
	m_MatArray[11] = d11;
	m_MatArray[12] = d12;
	m_MatArray[13] = d13;
	m_MatArray[14] = d14;
	m_MatArray[15] = d15;
}

void Matrix4::SetRow(int row, float *datas)
{
	for (int i = 0; i < 4; i++)
		m_MatArray[row * 4 + i] = datas[i];
}

void Matrix4::SetColumn(int column, float *datas)
{
	for (int i = 0; i < 4; i++)
		m_MatArray[column + 4 * i] = datas[i];
}

void Matrix4::SetIdentity()
{
	Set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

float* Matrix4::GetArray() const
{
	//TODO: c++배열 공부하기
	return m_MatArray;
}

Matrix4 Matrix4::operator+(const Matrix4 & other)
{
	return Matrix4();
}

Matrix4 Matrix4::operator-(const Matrix4 & other)
{
	return Matrix4();
}

Matrix4 Matrix4::operator*(const Matrix4 & other)
{
	return Matrix4();
}
