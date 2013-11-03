#ifndef OpenGL_h__
#define OpenGL_h__

#include <Windows.h>

// GLEW Libraries
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/GLU.h>

// GLM Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Settings/Settings.h"
#include "Shader.h"

// Typedefs
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

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
	void CreateSquare();
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
	unsigned VertexBufferObject[1];
};

#endif // OpenGL_h__
