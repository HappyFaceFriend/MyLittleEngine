#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(GLFWwindow *window) : m_Position(glm::vec3(0,0,0)), m_Forward(glm::vec3(0,0,1)),
				m_Up(glm::vec3(0,1,0)), m_Window(window)
{
	m_Right = glm::cross(-m_Up, m_Forward);
	m_ViewMatrix = glm::lookAt(
		m_Position,
		m_Position + m_Forward,
		m_Up
	);
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