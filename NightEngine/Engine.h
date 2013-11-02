#ifndef Engine_h__
#define Engine_h__

#include "Window/Window.h"
#include "Debugging/Macros.h"
#include "Settings/Settings.h"
#include "Rendering/OpenGL.h"
#include "Rendering/Shader.h"

class Engine
{

	Window* m_MainWindow;
	GameSettings* m_GameSettings;

public:

	bool Initialize(GameSettings *gameSettings);
	bool Run();
	bool Shutdown();
	bool MainEngineLoop();
};

extern Engine* g_Engine;
extern OpenGLContext* g_OpenGLContext;

#endif // Engine_h__
