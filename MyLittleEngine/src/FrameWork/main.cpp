#include "Application.h"
#include "../TestScene.h"
int main()
{
	Application application; //GLEW �ʱ�ȭ

	application.Run(new TestScene());

	return 0;
}
