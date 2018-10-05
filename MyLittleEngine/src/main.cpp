
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "VertexBuffer.h"
#include "GLDebug.h"
#include "VertexArray.h"
#include "Shader.h"

GLuint LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
std::string ParseShader(const std::string& filePath);

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW 초기화 실패\n" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ver 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //최신버전
	glewExperimental = true; //최신버전 받기위함

	GLFWwindow *window = glfwCreateWindow(800, 600, "MyLittleEngine", NULL, NULL);//새 창 열고 컨텍스트 생성
	if (window == NULL)
	{
		std::cout << "GLFW윈도우 실패" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window); //GLEW 초기화

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}
	//키입력 감지
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	typedef struct _vertex {
		float x, y, z;
	}Vertex;
	static const Vertex vertexDatas[] = {
		{-1.0f, -1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
		{0.0f,  1.0f, 0.0f },
	};
	VertexBuffer vb(sizeof(float) * 3 * 3 , vertexDatas);
	vb.Bind();
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	VertexArray va;
	va.AddBuffer(vb, layout);
	va.Bind();
	Shader shader = Shader("res/SimpleVertexShader.vertexshader", "res/SimpleFragmentShader.fragmentshader");
	shader.Bind();
	while (!glfwWindowShouldClose(window))
	{
		//그리는 부분

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		//GLCall(glDisableVertexAttribArray(0));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
