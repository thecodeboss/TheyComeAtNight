#include "Engine.h"

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

	return 0;
}
