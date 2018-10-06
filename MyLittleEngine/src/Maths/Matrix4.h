#pragma once
class Matrix4
{
private:
	float m_MatArray[16];
public:
	static const Matrix4 identity;
	Matrix4();
	Matrix4(float *datas);
	Matrix4(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10,
		float d11, float d12, float d13, float d14, float d15);
	~Matrix4();
	void Set(float *datas);
	void Set(float d0, float d1, float d2, float d3, float d4, float d5, float d6, float d7, float d8, float d9, float d10,
		float d11, float d12, float d13, float d14, float d15);
	void SetRow(int row, float *datas);
	void SetColumn(int column, float *datas);
	void SetIdentity();
	float* GetArray() const;
	Matrix4 operator+(const Matrix4& other);
	Matrix4 operator-(const Matrix4& other);
	Matrix4 operator*(const Matrix4& other);

};

