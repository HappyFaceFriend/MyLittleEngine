
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
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
	window.Init(640,480,"MyLittleEngine");
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

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");
	glUseProgram(programID);
	while (!window.WindowShouldClose())
	{
		//그리는 부분

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	std::string code;
	if (stream.is_open())
	{
		std::stringstream sstr;
		sstr << stream.rdbuf();
		code = sstr.str();
		stream.close();
	}
	else
	{
		printf("파일 %s를 읽을 수 없음", filePath);
		return 0;
	}
	return code;
}
void CompileShader(GLuint shaderID, const std::string& shaderCode)
{
	GLint result = GL_FALSE;
	const char* src = shaderCode.c_str();

	glShaderSource(shaderID, 1, &src, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int infoLogLength;
		char *msg;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		msg = new char[infoLogLength+1];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, msg);
		printf("%s\n",msg);
	}

}
GLuint LinkShaders(GLuint vertexShaderID, GLuint fragmentShaderID)
{
	GLint result = GL_FALSE;
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int infoLogLength;
		char *msg;
		glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		msg = new char[infoLogLength + 1];
		glGetShaderInfoLog(programID, infoLogLength, NULL, msg);
		printf("%s\n", msg);
	}
	return programID;
}
GLuint LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode = ParseShader(vertexShaderPath);
	std::string fragmentShaderCode = ParseShader(fragmentShaderPath);

	CompileShader(vertexShaderID, vertexShaderCode);
	CompileShader(fragmentShaderID, fragmentShaderCode);

	GLuint programID = LinkShaders(vertexShaderID, fragmentShaderID);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}
