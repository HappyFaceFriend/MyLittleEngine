#pragma once
#include <string>
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
namespace ML {
	class Window
	{
	private:
		unsigned int m_Height;
		unsigned int m_Width;
		std::string m_Title;
		GLFWwindow *m_Window;
	public:
		Window();
		bool Init(unsigned int width, unsigned int height, const std::string& title);
		bool WindowShouldClose();
		void SwapBuffers();
		~Window();

	};
}