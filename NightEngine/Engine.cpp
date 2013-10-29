#include "Debug/Macros.h"
#include "Engine.h"

Engine* g_Engine;

bool Engine::Init()
{
	m_MainWindow = new Window();
	CHECKPOINTER(m_MainWindow, "Failed to create window.")

	bool result = m_MainWindow->Initialize();
	CHECKFAIL(result, "Failed to initialize main Window")

	return result;
}

bool Engine::Run()
{
	MSG msg;

	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	bool done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do our engine loop
			bool bShouldClose = MainEngineLoop();
			if(bShouldClose)
			{
				done = true;
			}
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

//void UpdateCamera() 
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void UpdateSceneElements() 
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void RenderScene() 
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//void StartMenu()
//{
//	throw std::exception("The method or operation is not implemented.");
//}
//
//bool bIsGameRunning()
//{
//	throw std::exception("The method or operation is not implemented.");
//}

bool Engine::MainEngineLoop()
{
	//Menu();

	//if (! bIsGameRunning())
	//{
	//	continue;
	//}

	//UpdateCamera();

	//UpdateSceneElements();

	//RenderScene();

	//SwapBuffers();


	// This should return true when user quits.
	// Returns false for now so the window won't close right away.
	return false;
}
