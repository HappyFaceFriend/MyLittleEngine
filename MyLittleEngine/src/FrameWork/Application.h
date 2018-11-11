#pragma once
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
#include "SpriteRenderer.h"
#include "Scene.h"
class Application
{
private:
	bool InitGLFW();
	bool CreateWindow();
	bool InitGLEW();
	unsigned int m_Width;
	unsigned int m_Height;
	GLFWwindow *m_Window;
	static Renderer *m_Renderer;
	static SpriteRenderer *m_SpriteRenderer;
	Scene* nowScene;
public:
	Application();
	~Application();
	int Run(Scene *scene);
	static void RenderSprite(const Sprite& sprite);
};