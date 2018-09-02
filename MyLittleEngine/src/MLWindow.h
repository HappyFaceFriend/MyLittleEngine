#pragma once
#include <string>
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
namespace ML {
	class Window
	{
	private:
		int m_Height;
		int m_Width;
		std::string m_Title;
		GLFWwindow *m_Window;
	public:
		Window();
		bool Init(int width, int height, const std::string& title);
		bool WindowShouldClose();
		void SwapBuffers();
		~Window();

	};
}