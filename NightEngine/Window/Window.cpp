#include "Window.h"
#include "../Rendering/OpenGL.h"
#include "../Debugging/Macros.h"

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
			return 0;
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
	// Set an external pointer to this object.
	// This will become useful for callbacks.
	g_MainWindow = this;

	// Get the instance of this window.
	m_hinstance = GetModuleHandle(nullptr);

	// Handle the settings for the game
	m_GameSettings = gameSettings;

	// Setup the window with default settings for now.
	WNDCLASSEX WindowContext;
	WindowContext.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WindowContext.lpfnWndProc = WndProc;
	WindowContext.cbClsExtra = 0;
	WindowContext.cbWndExtra = 0;
	WindowContext.hInstance = m_hinstance;
	WindowContext.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	WindowContext.hIconSm = WindowContext.hIcon;
	WindowContext.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WindowContext.hbrBackground = nullptr;
	WindowContext.lpszMenuName = nullptr;
	WindowContext.lpszClassName = m_GameSettings->m_GameTitle;
	WindowContext.cbSize = sizeof(WNDCLASSEX);

	// Register the window
	RegisterClassEx(&WindowContext);

	int posX, posY;
	DWORD WindowExStyle, WindowStyle;

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

		// Set window style so there is no edge
		WindowExStyle = WS_EX_APPWINDOW;
		WindowStyle = WS_EX_TOPMOST | WS_POPUP;
	}
	else
	{
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - gameSettings->m_ScreenX)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - gameSettings->m_ScreenY) / 2;

		// Set window style to have an edge
		WindowExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		WindowStyle = WS_OVERLAPPEDWINDOW;
	}

	// Creating the Window handle could resize the screen, which in turn requires
	// an OpenGL context.  So we create it right before the Window.
	g_OpenGLContext = new OpenGLContext(gameSettings);

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WindowExStyle, m_GameSettings->m_GameTitle, m_GameSettings->m_GameTitle, WindowStyle, 
		posX, posY, gameSettings->m_ScreenX, gameSettings->m_ScreenY, nullptr, nullptr, m_hinstance, nullptr);

	g_OpenGLContext->CreateContext(m_hwnd, gameSettings); //Create our OpenGL context on the given window we just created

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

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
	if(PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

	return m_msg.message;
}
