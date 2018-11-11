#include "Application.h"
#include "../TestScene.h"
int main()
{
	Application application; //GLEW √ ±‚»≠

	application.Run(new TestScene());

	return 0;
}
