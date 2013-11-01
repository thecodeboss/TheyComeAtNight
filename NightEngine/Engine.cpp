#include "Debugging/Macros.h"
#include "Engine.h"

Engine* g_Engine;

bool Engine::Init( GameSettings *gameSettings )
{
	m_GameSettings = gameSettings;

	m_MainWindow = new Window();
	CHECKPOINTER(m_MainWindow, "Failed to create window.")

	bool result = m_MainWindow->Initialize(gameSettings);
	CHECKFAIL(result, "Failed to initialize main Window")

	return result;
}

bool Engine::Run()
{
	// Loop until there is a quit message from the window or the user.
	bool done = false;
	while(!done)
	{
		// Handle Windows messages
		// If windows signals to end the application then exit out.
		if(m_MainWindow->HandleMessages() == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do our engine loop
			done = MainEngineLoop();
		}

	}

	return true;
}

bool Engine::Shutdown()
{
	bool result = m_MainWindow->Shutdown();
	delete m_MainWindow;
	return result;
}

bool Engine::MainEngineLoop()
{
	//Menu();

	//if (! bIsGameRunning())
	//{
	//	continue;
	//}

	//UpdateCamera();

	//UpdateSceneElements();

	g_OpenGLContext->RenderScene(); 

	//SwapBuffers();


	// This should return true when user quits.
	// Returns false for now so the window won't close right away.
	return false;
}
