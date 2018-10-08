#pragma once
#include "Camera.h"
class MyCamera :
	public Camera
{
private:
	float m_Speed;
public:
	MyCamera(GLFWwindow *window);
	~MyCamera();

	void Move();
};

