#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(GLFWwindow *window) : m_Position(glm::vec3(0,0,-2)), m_Forward(glm::vec3(0,0,1)),
				m_Up(glm::vec3(0,1,0)), m_Window(window)
{
	m_Right = glm::cross(-m_Up, m_Forward);
	m_ViewMatrix = glm::lookAt(
		m_Position,
		m_Position + m_Forward,
		m_Up
	);
	m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)4 / (float)3, 0.1f, 100.0f);
}


Camera::~Camera()
{
}
void Camera::Update()
{
	m_ViewMatrix = glm::lookAt(
		m_Position,
		m_Position + m_Forward,
		m_Up
	);
}

//https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
void Camera::RotateAroundX(float rad)
{
	float x = m_Forward.x, y = m_Forward.y, z = m_Forward.z;
	m_Forward.x = x;
	m_Forward.y = y*cos(rad) - z*sin(rad);
	m_Forward.z = y*sin(rad) + z*cos(rad);
}
void Camera::RotateAroundY(float rad)
{
	float x = m_Forward.x, y = m_Forward.y, z = m_Forward.z;
	m_Forward.x = x*cos(rad) + z*sin(rad);
	m_Forward.y = y;
	m_Forward.z = -x*sin(rad) + z*cos(rad);
}
void Camera::RotateAroundZ(float rad)
{
	float x = m_Forward.x, y = m_Forward.y, z = m_Forward.z;
	m_Forward.x = x*cos(rad) - y*sin(rad);
	m_Forward.y = x*sin(rad) + y*cos(rad);
	m_Forward.z = z;
}