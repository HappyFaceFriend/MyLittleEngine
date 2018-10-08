#pragma once
#include "Camera.h"
class MyCamera :
	public Camera
{
private:
	float m_MoveSpeed;
	float m_RotSpeed;
	float m_HorizontalAngle;
	float m_VerticalAngle;
public:
	MyCamera(GLFWwindow *window, float moveSpeed, float rotSpeed);
	~MyCamera();

	void Move();
};

