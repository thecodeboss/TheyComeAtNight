#ifndef Window_h__
#define Window_h__

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

class Window
{

	HINSTANCE m_hinstance;
	HWND m_hwnd;
	LPCSTR m_WindowTitle;
	int m_ScreenWidth;
	int m_ScreenHeight;
	bool m_FullScreen;

public:

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	bool Initialize();
	bool Shutdown();
};

extern Window* g_MainWindow;

#endif // Window_h__
