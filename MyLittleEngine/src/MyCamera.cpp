#include "MyCamera.h"
#include <iostream>
extern float deltaTime;
static const float PI = 3.141592f;
MyCamera::MyCamera(GLFWwindow *window, float moveSpeed, float rotSpeed)
	: Camera(window), m_MoveSpeed(moveSpeed), m_RotSpeed(rotSpeed), m_HorizontalAngle(PI),
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
	m_HorizontalAngle += m_RotSpeed * deltaTime*float(width / 2 - xpos);
	m_VerticalAngle += m_RotSpeed * deltaTime*float(height / 2 - ypos);
	m_Forward = glm::vec3(
		cos(m_VerticalAngle) * sin(m_HorizontalAngle),
		sin(m_VerticalAngle),
		cos(m_VerticalAngle) * cos(m_HorizontalAngle)
	);
	std::cout << m_Forward.x <<" "<<m_Forward.y<<" "<<m_Forward.z << std::endl;
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
		m_HorizontalAngle = PI;
		m_VerticalAngle = 0;
	}


	/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		initialFoV -= 45 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		initialFoV += 45 * deltaTime;*/
}