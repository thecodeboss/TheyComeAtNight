#include "Window.h"

// -------------------------------
//        Global Variables
// -------------------------------
Window* g_MainWindow;

// -------------------------------
//        Global Functions
// -------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
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

bool Window::Initialize()
{
	// Set an external pointer to this object.
	// This will become useful for callbacks.
	g_MainWindow = this;

	// Get the instance of this window.
	m_hinstance = GetModuleHandle(NULL);

	m_WindowTitle = "Game Engine (Change This)";

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
	wc.lpszClassName = m_WindowTitle;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window
	RegisterClassEx(&wc);

	// Determine the resolution of the user's screen.
	m_ScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	int posX, posY;

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(m_FullScreen)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)m_ScreenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_ScreenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		m_ScreenWidth  = 800;
		m_ScreenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_ScreenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_ScreenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, m_WindowTitle, m_WindowTitle, WS_OVERLAPPEDWINDOW, posX, posY, m_ScreenWidth, m_ScreenHeight, NULL, NULL, m_hinstance, NULL);

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
