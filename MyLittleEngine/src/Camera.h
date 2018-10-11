#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
class Camera
{
protected:
	GLFWwindow *m_Window;
	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
protected:
	Camera(GLFWwindow *window);
	virtual ~Camera();
public:
	void Update();
	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::vec3 GetForward() { return m_Forward; }
	inline glm::vec3 GetRight() { return m_Right; }
	inline glm::vec3 GetUp() { return m_Up;  }
	inline glm::mat4 GetViewMatrix() { return m_ViewMatrix;  }
	inline glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }


	void RotateAroundX(float rad);
	void RotateAroundY(float rad);
	void RotateAroundZ(float rad);
};

