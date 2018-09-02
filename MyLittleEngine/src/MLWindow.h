#pragma once
#include <string>
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
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