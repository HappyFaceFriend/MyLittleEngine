#include "Renderer.h"
#include "GLDebug.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Render() const
{
	GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr));
}
void Renderer::BindObjects(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
{
	va.Bind();
	ib.Bind();
	shader.Bind();
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}