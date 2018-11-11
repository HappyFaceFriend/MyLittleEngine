#pragma once
#include "MyLittleGLContents.h"
#include "Math\Vector2.h"
class Sprite
{
private:
	Texture *m_Texture;
	Vector2 m_Position;
	int m_Width;
	int m_Height;
public:
	Sprite(const std::string& filePath, int x, int y);
	~Sprite();

	void Update();
	void Render();

	void Translate(float x, float y);
	void Translate(const Vector2& vec);

	inline const Texture& GetTexture() const { return *m_Texture; };

	inline Vector2 GetPosition() const { return m_Position; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
};

