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
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);//�� â ���� ���ؽ�Ʈ ����
	if (m_Window == NULL)
	{
		std::cout << "GLFW������ ����" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window); //GLEW �ʱ�ȭ

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}
	//Ű�Է� ����
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

}

bool ML::Window::WindowShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

void ML::Window::SwapBuffers()
{
	//���۱�ü
	glfwSwapBuffers(m_Window);
}


ML::Window::~Window()
{
}
