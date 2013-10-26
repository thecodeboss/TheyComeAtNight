<<<<<<< HEAD
#include "../Engine/Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	g_Engine = new Engine();
	bool result = g_Engine->Init();
	CHECKFAIL(result, "Failed to initialize the game engine.")

	result = g_Engine->Run();
	CHECKFAIL(result, "Engine stopped running unexpectedly.")

	result = g_Engine->Shutdown();
	CHECKFAIL(result, "Engine shutdown failed.")
	delete g_Engine;

=======

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
>>>>>>> 7c169298f8ca83c1f973af282b06b885935d27b0
	return 0;
}
