#pragma once

class Object
{
public:
	Object() {}
	~Object() {}

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};