#ifndef Engine_h__
#define Engine_h__

#include "Window/Window.h"
#include "Debug/Macros.h"
#include "Settings/Settings.h"

class Engine
{

	Window* m_MainWindow;
	GameSettings* m_GameSettings;

public:

	bool Init(GameSettings *gameSettings);
	bool Run();
	bool Shutdown();
	bool MainEngineLoop();
};

extern Engine* g_Engine;

#endif // Engine_h__
