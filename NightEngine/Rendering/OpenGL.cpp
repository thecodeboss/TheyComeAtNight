#include "OpenGL.h"
#include "../Debugging/Macros.h"

OpenGLContext::OpenGLContext(GameSettings* gameSettings /* = nullptr */) : bSceneReady(false)
{
	m_GameSettings = gameSettings;
}

OpenGLContext::OpenGLContext(HWND WindowIdentifier, GameSettings* gameSettings) : bSceneReady(false) {
	CreateContext(WindowIdentifier, gameSettings); // Create a context given a WindowsIdentifier
}

OpenGLContext::~OpenGLContext() {
	wglMakeCurrent(m_DeviceContext, 0); // Remove the rendering context from our device context
	wglDeleteContext(m_RenderingContext); // Delete our rendering context

	ReleaseDC(m_WindowIdentifier, m_DeviceContext); // Release the device context from our window
}

bool OpenGLContext::CreateContext(HWND WindowIdentifier, GameSettings* gameSettings) {
	m_WindowIdentifier = WindowIdentifier; // Set the WindowsIdentifier for our window
	m_GameSettings = gameSettings;

	m_DeviceContext = GetDC(WindowIdentifier); // Get the device context for our window

	PIXELFORMATDESCRIPTOR PixelDescription; // Create a new PIXELFORMATDESCRIPTOR (PFD)
	memset(&PixelDescription, 0, sizeof(PIXELFORMATDESCRIPTOR)); // Clear our  PFD
	PixelDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR); // Set the size of the PFD to the size of the class
	PixelDescription.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW; // Enable double buffering, opengl support and drawing to a window
	PixelDescription.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
	PixelDescription.cColorBits = 32; // Give us 32 bits of color information (the higher, the more colors)
	PixelDescription.cDepthBits = 32; // Give us 32 bits of depth information (the higher, the more depth levels)
	PixelDescription.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD

	int pixelFormat = ChoosePixelFormat(m_DeviceContext, &PixelDescription);
	if (pixelFormat == 0) return false;

	BOOL Result = SetPixelFormat(m_DeviceContext, pixelFormat, &PixelDescription);
	if (!Result) return false;

	//not sure if belongs in OpenGLContext
	HGLRC TempOpenGLContext = wglCreateContext(m_DeviceContext); // Create an OpenGL 2.1 context for our device context
	wglMakeCurrent(m_DeviceContext, TempOpenGLContext); // Make the OpenGL 2.1 context current and active

	GLenum error = glewInit(); // Enable GLEW
	if (error != GLEW_OK) return false; // If GLEW fails

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3, // Set the MAJOR version of OpenGL to 3
		WGL_CONTEXT_MINOR_VERSION_ARB, 2, // Set the MINOR version of OpenGL to 2
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
		m_RenderingContext = wglCreateContextAttribsARB(m_DeviceContext, nullptr, attributes); // Create and OpenGL 3.x context based on the given attributes
		wglMakeCurrent(nullptr, nullptr); // Remove the temporary context from being active
		wglDeleteContext(TempOpenGLContext); // Delete the temporary OpenGL 2.1 context
		wglMakeCurrent(m_DeviceContext, m_RenderingContext); // Make our OpenGL 3.0 context current
	}
	else {
		m_RenderingContext = TempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context
	}

	return true; // We have successfully created a context, return true
}

void OpenGLContext::SetupScene()
{
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f); // Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	PrintErrors();

	m_Shader = new Shader();
	m_Shader->Initialize("NightEngine\\Rendering\\Shaders\\Shader.vert", "NightEngine\\Rendering\\Shaders\\Shader.frag");
	PrintErrors();

	bSceneReady = true;
}

void OpenGLContext::ReshapeWindow( unsigned x, unsigned y )
{
	m_GameSettings->m_ScreenX = x; // Set the window width
	m_GameSettings->m_ScreenY = y; // Set the window height
	if (bSceneReady) RenderScene();
}

void OpenGLContext::RenderScene() {
	glViewport(0, 0, m_GameSettings->m_ScreenX, m_GameSettings->m_ScreenY); // Set the viewport size to fill the window
	PrintErrors();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers
	PrintErrors();

	m_Shader->Bind();
	PrintErrors();

	m_Shader->Unbind();
	PrintErrors();

	SwapBuffers(m_DeviceContext); // Swap buffers so we can see our rendering
	PrintErrors();
}

void OpenGLContext::PrintErrors()
{
	GLenum Error = glGetError();
	if( Error != GL_NO_ERROR )
	{
		DEBUG_PRINT("OpenGL Error: " << gluErrorString(Error) << "\n")
	}
}
