#include "MyCamera.h"

extern float deltaTime;

MyCamera::MyCamera(GLFWwindow *window) : Camera(window), m_Speed(3.f)
{
}


MyCamera::~MyCamera()
{
}

void MyCamera::Move()
{
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += m_Forward * deltaTime*m_Speed;
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= m_Forward * deltaTime*m_Speed;
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= m_Forward * deltaTime*m_Speed;
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += m_Forward * deltaTime*m_Speed;
}