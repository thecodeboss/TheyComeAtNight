#ifndef OpenGL_h__
#define OpenGL_h__

#include <Windows.h>
#include "GL.h"
#include "../Settings/Settings.h"
#include "Shader.h"
#include "Model.h"

class OpenGLContext
{
public:
	OpenGLContext(GameSettings* gameSettings = nullptr);
	OpenGLContext(HWND WindowIdentifier, GameSettings* gameSettings);
	~OpenGLContext();
	bool CreateContext(HWND WindowIdentifier, GameSettings* gameSettings);
	void SetupScene();
	void ReshapeWindow(unsigned x, unsigned y);
	void RenderScene();
	void PrintErrors();
private:
	HGLRC m_RenderingContext;
	HDC m_DeviceContext;
	HWND m_WindowIdentifier;
	GameSettings* m_GameSettings;
	Shader* m_Shader;
	bool bSceneReady;
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ModelMatrix;
	unsigned VertexArrayObject[1];
	unsigned VertexBufferObject[2]; //two buffers, one for vertices and one for color
	unsigned m_NumModels;
	Model** m_Models; // @TODO: Move this into a 'Scene' class
};

#endif // OpenGL_h__
