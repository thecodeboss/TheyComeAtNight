
#include "Menu.h"

using namespace std;

void UpdateCamera() 
{
	throw std::exception("The method or operation is not implemented.");
}

void UpdateSceneElements() 
{
	throw std::exception("The method or operation is not implemented.");
}

void RenderScene() 
{
	throw std::exception("The method or operation is not implemented.");
}

void StartMenu()
{
	throw std::exception("The method or operation is not implemented.");
}

bool bIsGameRunning()
{
	throw std::exception("The method or operation is not implemented.");
}

int main()
{

	while (true) {

		Menu();

		if (! bIsGameRunning())
		{
			continue;
		}

		UpdateCamera();

		UpdateSceneElements();

		RenderScene();

		//SwapBuffers();
	}
	return 0;
}
