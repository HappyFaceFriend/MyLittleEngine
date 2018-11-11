#include "Sprite.h"
#include "Application.h"

Sprite::Sprite(const std::string& filePath, int x, int y)
	:m_Position(x,y)
{
	m_Texture = new Texture(filePath);
	m_Width = m_Texture->GetWidth();
	m_Height = m_Texture->GetHeight();
}


Sprite::~Sprite()
{
	delete m_Texture;
}
void Sprite::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}
void Sprite::Translate(const Vector2& vec)
{
	m_Position += vec;
}


void Sprite::Update()
{

}
void Sprite::Render()
{
	Application::RenderSprite(*this);
}