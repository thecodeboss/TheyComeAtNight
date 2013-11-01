#include "Window.h"
#include "../Rendering/OpenGL.h"

// -------------------------------
//        Global Variables
// -------------------------------
Window* g_MainWindow;
OpenGLContext* g_OpenGLContext;

// -------------------------------
//        Global Functions
// -------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
	case WM_SIZE:
		{
			g_OpenGLContext->ReshapeWindow(LOWORD(lparam), HIWORD(lparam));
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}
	default:
		{
			return g_MainWindow->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

// -------------------------------
//        Member Functions
// -------------------------------

LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
	case WM_KEYDOWN:
		{
			//Do nothing for now
		}
	case WM_KEYUP:
		{
			// Do nothing for now
		}
	default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

bool Window::Initialize( GameSettings* gameSettings )
{
	// Initialize the message structure.
	ZeroMemory(&m_msg, sizeof(MSG));

	// Set an external pointer to this object.
	// This will become useful for callbacks.
	g_MainWindow = this;

	// Get the instance of this window.
	m_hinstance = GetModuleHandle(NULL);

	// Handle the settings for the game
	m_GameSettings = gameSettings;

	// Setup the window with default settings for now.
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_GameSettings->m_GameTitle;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window
	RegisterClassEx(&wc);

	int posX, posY;

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(gameSettings->m_bFullScreen)
	{
		// Determine the resolution of the user's screen.
		gameSettings->m_ScreenX  = GetSystemMetrics(SM_CXSCREEN);
		gameSettings->m_ScreenY = GetSystemMetrics(SM_CYSCREEN);

		// If full screen set the screen to maximum size of the users desktop and 32bit.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)gameSettings->m_ScreenX;
		dmScreenSettings.dmPelsHeight = (unsigned long)gameSettings->m_ScreenY;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - gameSettings->m_ScreenX)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - gameSettings->m_ScreenY) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, m_GameSettings->m_GameTitle, m_GameSettings->m_GameTitle, WS_OVERLAPPEDWINDOW, 
		posX, posY, gameSettings->m_ScreenX, gameSettings->m_ScreenY, NULL, NULL, m_hinstance, NULL);

	g_OpenGLContext->CreateContext(m_hwnd, gameSettings); //Create our OpenGL context on the given window we just created

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	g_OpenGLContext->SetupScene(); // Setup our OpenGL scene

	// Hide the mouse cursor.
	// ShowCursor(false);

	return true;
}

bool Window::Shutdown()
{
	return true;
}

unsigned Window::HandleMessages()
{
	// Handle the windows messages.
	if(PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

	return m_msg.message;
}
