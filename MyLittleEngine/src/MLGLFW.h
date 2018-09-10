#pragma once
#include <iostream>
#include <GL/glew.h>	//opengl의 추가적 기능
#include <GLFW/glfw3.h>	//윈도우 생성을 위함
namespace ML {
	bool InitGLFW()
	{
		if (!glfwInit())
		{
			std::cout << "GLFW 초기화 실패\n" << std::endl;
			return false;
		}
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ver 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //최신버전
		glewExperimental = true; //최신버전 받기위함
		return true;
	}
	void PollEvents()
	{

		//이벤트 막힌것 실행
		glfwPollEvents();
	}
}