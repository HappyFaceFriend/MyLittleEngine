#pragma once
#include <string>
#include <GL/glew.h>
class Shader
{
private:
	unsigned int m_Id;
	std::string ParseShader(const std::string& filePath);
	void CompileShader(GLuint shaderID, const std::string& shaderCode);
	void LinkShaders(GLuint vertexShaderID, GLuint fragmentShaderID);
	void LoadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;
};

