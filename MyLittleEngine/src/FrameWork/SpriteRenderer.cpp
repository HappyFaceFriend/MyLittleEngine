#include "SpriteRenderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

SpriteRenderer::SpriteRenderer()
	: Projection(glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f)),
	View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
{
	static const GLfloat spriteVerticies[] = {
		0.0f,0.0f, 0.0f,0.0f,
		1.0f,0.0f, 1.0f,0.0f,
		1.0f,1.0f, 1.0f,1.0f,
		0.0f,1.0f, 0.0f,1.0f
	};
	static const GLuint spriteIndicies[] = {
		0,1,2,
		2,3,0
	};
	m_VBO = new VertexBuffer(sizeof(float) * 4 * 4, spriteVerticies);
	m_IBO = new IndexBuffer(spriteIndicies, 3 * 2);
	VertexBufferLayout layout;
	layout.Push(GL_FLOAT, 2);
	layout.Push(GL_FLOAT, 2);
	m_VAO = new VertexArray();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_SpriteShader = new Shader("res/SimpleVertexShader.vertexshader", "res/SimpleFragmentShader.fragmentshader");
	m_SpriteShader->SetUniform1i("myTextureSampler", 0);

}


SpriteRenderer::~SpriteRenderer()
{
	delete m_VBO;
	delete m_VAO;
	delete m_SpriteShader;
	delete m_IBO;
}
void SpriteRenderer::Render(const Sprite& sprite, const Renderer& renderer)
{
	glm::vec3 pos = glm::vec3(sprite.GetPosition().x, sprite.GetPosition().y, 0);
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(sprite.GetWidth(), sprite.GetHeight(), 1));
	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), pos);
	Model = transMat * scaleMat * Model;
	glm::mat4 mvp = Projection * View * Model;
	m_SpriteShader->SetUniformMat4("mvp", mvp);
	sprite.GetTexture().Bind();
	renderer.Render(*m_VAO, *m_IBO, *m_SpriteShader);
}
