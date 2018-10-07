
#include <GL/glew.h>	//opengl�� �߰��� ���
#include <GLFW/glfw3.h>	//������ ������ ����
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "MyLittleGLContents.h"
#include "stb_image\stb_image.h"
#include "GLContents\Controls.h"

GLFWwindow *window;
glm::mat4 Projection, View, Model;

glm::vec3 position = glm::vec3(-3, 3, 7);
float horizontalAngle = 3.14f;
float verticalAngle = 0.f;
float initialFoV = 45.f; //field of view
float speed = 3.f;
float mouseSpeed = 0.05f;
float deltaTime = 0.016;
double currentTime = glfwGetTime();
double lastTime;

GLuint loadBMP_custom(const char * imagePath)
{
	unsigned char header[54];//bmp file begins with 54byte header
	unsigned int position;
	unsigned int width, height,bpp;
	unsigned int imageSize; //=w*h*3
	unsigned char *data;
	
	FILE *file; fopen_s(&file, imagePath, "rb");
	if (file == NULL)
	{
		std::cout << "Could not open image " << imagePath << std::endl;
		return 0;
	}
	if (fread(header, 1, 54, file) != 54 || header[0]!='B' || header[1]!='M')
	{
		std::cout << imagePath << " is not a bmp file" << std::endl;
		return 0;
	}
	position	= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);
	//if (imageSize == 0)
		imageSize = width*height * 3;
	//if (position == 0)
		position = 54;
	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	/*stbi_set_flip_vertically_on_load(1);
	data = stbi_load(imagePath, &width, &height, &bpp, 4);
	*/
	GLuint textureID;
	glGenTextures(1, &textureID);

	GLCall(glActiveTexture(GL_TEXTURE0 + 0));
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//delete data;
	return textureID;
}


void computeMatricesFromInputs()
{
	//TODO:��ü������
	lastTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);

	double dx, dy;
	glfwGetCursorPos(window, &dx, &dy);
	glfwSetCursorPos(window, 800 / 2, 600 / 2);
	horizontalAngle += mouseSpeed*deltaTime*float(800 / 2 - dx);
	verticalAngle += mouseSpeed*deltaTime*float(600 / 2 - dy);
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 front(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.141592f / 2.f),
		0,
		cos(verticalAngle - 3.141592f / 2.f)
	);
	glm::vec3 up = glm::cross(right, front);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += front*deltaTime*speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= front*deltaTime*speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= right*deltaTime*speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += right*deltaTime*speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		initialFoV -= 45 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		initialFoV += 45 * deltaTime;
	Projection = glm::perspective(glm::radians(initialFoV), 4 / 3.f, 0.1f, 100.f);
	View = glm::lookAt(
		position,
		position + front,
		up
	);
}
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

	window = glfwCreateWindow(800, 600, "MyLittleEngine", NULL, NULL);//�� â ���� ���ؽ�Ʈ ����
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
	//For index buffers
	/*static const float vertexDatas[] = {
		-1.0f, 1.0f, -1.0f ,
		-1.0f, 1.0f, 1.0f ,
		1.0f, 1.0f, 1.0f ,
		1.0f, 1.0f, -1.0f ,
		-1.0f, -1.0f, -1.0f ,
		-1.0f, -1.0f, 1.0f ,
		1.0f, -1.0f, 1.0f ,
		1.0f, -1.0f, -1.0f ,
	};
	static const float vertexColors[] = {
		1,0,0,
		1,0,0.25,
		1,0,0.5,
		1,0,1,
		0,1,0,
		0,1,0.25,
		0,1,0.5,
		0,1,1
	};
	static const unsigned int indicies[] = {
		0,1,3,
		1,2,3,
		1,5,2,
		2,5,6,
		4,5,6,
		4,6,7,
		0,4,7,
		0,3,7,
		0,1,4,
		1,4,5,
		2,3,6,
		3,6,7
	};*/
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	static const GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};
	static const GLfloat g_uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};
	VertexBuffer vb(sizeof(float) * 3 * 36, g_vertex_buffer_data);
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 3);
	//VertexBuffer vb2(sizeof(float) * 3 * 36, g_color_buffer_data);
	VertexBuffer vb3(sizeof(float) * 2 * 36 ,g_uv_buffer_data);
	VertexBufferLayout layout2;
	layout2.Push(GL_FLOAT, 2);
	VertexArray va;
	va.AddBuffer(vb, layout);
	//va.AddBuffer(vb2, layout);
	va.AddBuffer(vb3, layout2);
	va.Bind();

	//IndexBuffer ib(indicies, 12*3);
	//ib.Bind();

	Shader shader = Shader("res/SimpleVertexShader.vertexshader", "res/SimpleFragmentShader.fragmentshader");
	shader.Bind();

	Renderer renderer;

	GLuint texture = loadBMP_custom("res/temp.bmp");

	shader.SetUniform1i("myTextureSampler", 0);

	Model = glm::mat4(1.f);
	/*glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
		glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
		glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
	);*/
	View = glm::lookAt(
		glm::vec3(-3, 3, 7), 
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);
	// �������� ��Ʈ���� : 45�� �þ߰�, 4:3 ����, �þ� ���� : 0.1 ���� <--> 100 ����
	Projection = glm::perspective(glm::radians(45.0f), (float)4 / (float)3, 0.1f, 100.0f);
	//glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	glm::mat4 mvp = Projection * View * Model;



	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	while (!glfwWindowShouldClose(window))
	{

		//�׸��� �κ�
		renderer.Clear();

	
		computeMatricesFromInputs();
		//Projection = getProjectionMatrix();
		//View = getViewMatrix();
		glm::mat4 mvp = Projection * View * Model;
		shader.SetUniformMat4("mvp", mvp);

		renderer.Render(va, shader, 12 * 3);
		//GLCall(glDisableVertexAttribArray(0));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
