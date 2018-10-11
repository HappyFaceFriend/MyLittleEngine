#include "MyCamera.h"
#include <iostream>
extern float deltaTime;
static const float PI = 3.141592f;
MyCamera::MyCamera(GLFWwindow *window, float moveSpeed, float rotSpeed)
	: Camera(window), m_MoveSpeed(moveSpeed), m_RotSpeed(rotSpeed), m_HorizontalAngle(0),
	m_VerticalAngle(0.f)
{
}

MyCamera::~MyCamera()
{
}

void MyCamera::Move()
{
	int width, height;
	double xpos, ypos;
	glfwGetCursorPos(m_Window, &xpos, &ypos);
	glfwGetWindowSize(m_Window, &width, &height);
	glfwSetCursorPos(m_Window, width / 2, height/ 2);

	//y축기준, y가 움직이면 안됨
	m_HorizontalAngle = m_RotSpeed * deltaTime*float(width / 2 - xpos);
	//x축 기준, x가 움직이면 안됨
	m_VerticalAngle = m_RotSpeed * deltaTime*float(height / 2 - ypos);


	if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_HorizontalAngle = -0.01;
	if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		m_HorizontalAngle = 0.01;

	if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
		m_VerticalAngle = -0.01;
	if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_VerticalAngle = 0.01;

	/*
	m_Forward = glm::vec3(
		sin(m_HorizontalAngle) * cos(m_VerticalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);
	*/
	RotateAroundY(-m_HorizontalAngle);
	RotateAroundX(m_VerticalAngle);
	std::cout << m_Forward.x <<" \t"<< m_Forward.y<<" \t"<< m_Forward.z << std::endl;
	m_Right = glm::vec3(
		sin(m_HorizontalAngle - PI / 2.f),
		0,
		cos(m_VerticalAngle - PI / 2.f)
	);
	m_Up = glm::cross(m_Right, m_Forward);
	
	//TODO : 카메라 조 ㅁ제대로
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += m_Forward * deltaTime*m_MoveSpeed;
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= m_Forward * deltaTime*m_MoveSpeed;
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= m_Right * deltaTime*m_MoveSpeed;
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += m_Right * deltaTime*m_MoveSpeed;
	if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_HorizontalAngle = 0;
		m_VerticalAngle = 0;
	}


	/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		initialFoV -= 45 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		initialFoV += 45 * deltaTime;*/
}
