#ifndef OpenGL_h__
#define OpenGL_h__

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "../Settings/Settings.h"

class OpenGLContext 
{
public:
	OpenGLContext();
	OpenGLContext(HWND WindowIdentifier, GameSettings* gameSettings);
	~OpenGLContext();
	bool CreateContext(HWND WindowIdentifier, GameSettings* gameSettings);
	void SetupScene();
	void ReshapeWindow(unsigned x, unsigned y);
	void RenderScene();

private:
	HGLRC m_RenderingContext;
	HDC m_DeviceContext;
	HWND m_WindowIdentifier;
	GameSettings* m_GameSettings;
};

#endif // OpenGL_h__
