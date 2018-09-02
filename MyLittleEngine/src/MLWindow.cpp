#include "MLWindow.h"
#include <iostream>

ML::Window::Window() : m_Width(1024), m_Height(768), m_Title("Title")
{
}

bool ML::Window::Init(int width, int height, const std::string& title)
{
	m_Width = width;
	m_Height = height;
	m_Title = title;
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);//새 창 열고 컨텍스트 생성
	if (m_Window == NULL)
	{
		std::cout << "GLFW윈도우 실패" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window); //GLEW 초기화

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}
	//키입력 감지
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

}

bool ML::Window::WindowShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void ML::Window::SwapBuffers()
{
	//버퍼교체
	glfwSwapBuffers(m_Window);
}


ML::Window::~Window()
{
}
