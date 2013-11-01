#ifndef Window_h__
#define Window_h__

#include <windows.h>
#include "../Settings/Settings.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

class Window
{

	HINSTANCE m_hinstance;
	HWND m_hwnd;
	MSG m_msg;
	GameSettings* m_GameSettings;

public:

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	bool Initialize(GameSettings* gameSettings);
	bool Shutdown();
	unsigned HandleMessages();
};

extern Window* g_MainWindow;

#endif // Window_h__
