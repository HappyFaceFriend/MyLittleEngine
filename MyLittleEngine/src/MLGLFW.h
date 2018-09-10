#pragma once
#include <iostream>
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
namespace ML {
	bool InitGLFW()
	{
		if (!glfwInit())
		{
			std::cout << "GLFW �ʱ�ȭ ����\n" << std::endl;
			return false;
		}
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x ��Ƽ���ϸ����
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ver 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //�ֽŹ���
		glewExperimental = true; //�ֽŹ��� �ޱ�����
		return true;
	}
	void PollEvents()
	{

		//�̺�Ʈ ������ ����
		glfwPollEvents();
	}
}