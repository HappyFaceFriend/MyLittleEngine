#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Render() const;
	void BindObjects(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Clear() const;
};

