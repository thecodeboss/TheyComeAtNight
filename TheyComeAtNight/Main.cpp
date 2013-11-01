#include "Engine.h"
#include "Settings/Settings.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	// Initialize the game's settings
	// In the future probably read this from a file
	GameSettings * gameSettings = new GameSettings("They Come At Night", /* Full Screen = */ true);

	g_Engine = new Engine();
	bool result = g_Engine->Init(gameSettings);
	CHECKFAIL(result, "Failed to initialize the game engine.")

	result = g_Engine->Run();
	CHECKFAIL(result, "Engine stopped running unexpectedly.")

	result = g_Engine->Shutdown();
	CHECKFAIL(result, "Engine shutdown failed.")
	delete g_Engine;

	return 0;
}
