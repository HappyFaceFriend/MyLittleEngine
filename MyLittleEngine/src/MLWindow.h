#pragma once
#include <string>
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
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