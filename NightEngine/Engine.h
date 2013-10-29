#ifndef Engine_h__
#define Engine_h__

#include "Window/Window.h"
#include "Debug/Macros.h"

class Engine
{

	Window* m_MainWindow;

public:

	bool Init();
	bool Run();
	bool Shutdown();
	bool MainEngineLoop();
};

extern Engine* g_Engine;

#endif // Engine_h__
