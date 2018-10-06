
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "MyLittleGLContents.h"
#include "Maths/Vector4.h"

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

	Vector4 vec1(1, 1, 1, 1);
	Vector4 vec2(2, 3, 4, 1);
	vec1 = vec1 + vec2;
	std::cout << vec1 << std::endl;

	typedef struct _vertex {
		float x, y, z;
	}Vertex;
	static const Vertex vertexDatas[] = {
		{-1.0f, -1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
		{0.0f,  1.0f, 0.0f },
	};
	static const unsigned int indicies[] = {
		0,1,2
	};
	VertexBuffer vb(sizeof(float) * 3 * 3 , vertexDatas);
	vb.Bind();

	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	VertexArray va;
	va.AddBuffer(vb, layout);
	va.Bind();

	IndexBuffer ib(indicies, 3);
	ib.Bind();

	Shader shader = Shader("res/SimpleVertexShader.vertexshader", "res/SimpleFragmentShader.fragmentshader");
	shader.Bind();

	Renderer renderer;
	renderer.BindObjects(va, ib, shader);

	while (!glfwWindowShouldClose(window))
	{
		//�׸��� �κ�
		renderer.Clear();
		renderer.Render();
		//GLCall(glDisableVertexAttribArray(0));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
