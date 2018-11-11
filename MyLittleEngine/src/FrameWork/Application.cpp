#include "Application.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyLittleGLContents.h"
#include "stb_image\stb_image.h"


float deltaTime = 0.016;
double currentTime;
double lastTime = glfwGetTime();


Renderer* Application::m_Renderer=nullptr;
SpriteRenderer* Application::m_SpriteRenderer=nullptr;

Application::Application()
	:m_Width(800), m_Height(600)
{
	InitGLFW(); 
	CreateWindow();
	InitGLEW();
	GLCall(glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE));
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	m_Renderer = new Renderer();
	m_SpriteRenderer = new SpriteRenderer();
}
Application::~Application()
{
	delete m_SpriteRenderer;
	delete m_Renderer;
	glfwTerminate();
}

int Application::Run(Scene *scene)
{
	//Sprite sp1 = Sprite("player.png");
	nowScene = scene;
	Sprite sprite1 = Sprite("res/player.png", 100, 100);
	Sprite sprite2 = Sprite("res/fartAni4.png",200,100);

	while (!glfwWindowShouldClose(m_Window))
	{
		currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		
		//그리는 부분
		m_Renderer->Clear();
		nowScene->Update(deltaTime);
		nowScene->Render();

		//GLCall(glDisableVertexAttribArray(0));
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	return 0;
}

void Application::RenderSprite(const Sprite& sprite)
{
	m_SpriteRenderer->Render(sprite, *m_Renderer);
}
bool Application::InitGLFW()
{
	if (!glfwInit())
	{
		std::cout << "GLFW 초기화 실패\n" << std::endl;
		ABORT();
		return false;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ver 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //최신버전
	glewExperimental = true; //최신버전 받기위함

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}
bool Application::InitGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		ABORT();
		return false;
	}
	return true;
}
bool Application::CreateWindow()
{
	m_Window = glfwCreateWindow(m_Width, m_Height, "MyLittleEngine", NULL, NULL);//새 창 열고 컨텍스트 생성

	if (m_Window == NULL)
	{
		std::cout << "GLFW윈도우 실패" << std::endl;
		glfwTerminate();
		ABORT();
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	return true;
}