
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
#include <string>
#include <fstream>
#include <sstream>

#include "GLDebug.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


GLuint LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
std::string ParseShader(const std::string& filePath);

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW �ʱ�ȭ ����\n" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x ��Ƽ���ϸ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ver 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //�ֽŹ���
	glewExperimental = true; //�ֽŹ��� �ޱ�����

	GLFWwindow *window = glfwCreateWindow(800, 600, "MyLittleEngine", NULL, NULL);//�� â ���� ���ؽ�Ʈ ����
	if (window == NULL)
	{
		std::cout << "GLFW������ ����" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window); //GLEW �ʱ�ȭ

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return false;
	}
	//Ű�Է� ����
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	typedef struct _vertex {
		float x, y, z;
	}Vertex;
	static const Vertex vertexDatas[] = {
		{-1.0f, -1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
		{0.0f,  1.0f, 0.0f },
	};
	VertexBuffer vb(sizeof(float) * 3, vertexDatas);
	//vb.Bind();

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("res/SimpleVertexShader.vertexshader", "res/SimpleFragmentShader.fragmentshader");

	while (!glfwWindowShouldClose(window))
	{
		//�׸��� �κ�

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,			//0��°�Ӽ� (shader�� layout�� ��Ī�ž���)
			3,			//count
			GL_FLOAT,	//type
			GL_FALSE,	//normalize
			0,			//stride
			(void*)0	//offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

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
		std::cout << "������ ���� �� ����:" << filePath << std::endl;
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
		glGetProgramInfoLog(programID, infoLogLength, NULL, msg);
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
