#include "TestScene.h"

TestScene::TestScene()
{
	sprite1 = new Sprite("res/player.png",100,100);
}
TestScene::~TestScene()
{
	delete sprite1;
}
void TestScene::Update(float deltaTime)
{
	sprite1->Translate(Vector2(100.0f,100.0f)*deltaTime);
}
void TestScene::Render()
{
	sprite1->Render();
}