
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>

#include "MLGLFW.h"
#include "MLWindow.h"

using namespace ML;

GLuint LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
std::string ParseShader(const std::string& filePath);
int main()
{
	if (!InitGLFW())
		return -1;

	Window window;
	window.Init(1024,768,"MyLittleEngine");
	typedef struct _vertex {
		float x, y, z;
	}Vertex;
	static const Vertex g_vertex_buffer_data[] = {
		{-1.0f, -1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
		{0.0f,  1.0f, 0.0f },
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer); //vb한개 생성
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	while (!window.WindowShouldClose())
	{
		//그리는 부분
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(
			0,			//0번째속성 (shader의 layout과 매칭돼야함)
			3,			//count
			GL_FLOAT,	//type
			GL_FALSE,	//normalize
			0,			//stride
			(void*)0	//offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		window.SwapBuffers();
		PollEvents();
	}

	return 0;
}

std::string ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string line;
}

GLuint LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{

}
