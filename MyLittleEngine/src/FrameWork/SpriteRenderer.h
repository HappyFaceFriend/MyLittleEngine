#pragma once
#include "MyLittleGLContents.h"
#include "Sprite.h"
class SpriteRenderer
{
private:
	VertexBuffer* m_VBO;
	IndexBuffer* m_IBO;
	VertexArray* m_VAO;
	Shader* m_SpriteShader;
	glm::mat4 Projection;
	glm::mat4 View;
	
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Render(const Sprite& sprite, const Renderer& renderer);
};

