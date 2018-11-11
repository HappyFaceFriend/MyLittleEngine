#pragma once
#include "Scene.h"
#include "Sprite.h"
class TestScene : public Scene
{
private:
	Sprite *sprite1;
public:
	TestScene();
	~TestScene();
	void Update(float deltaTime);
	void Render();
};