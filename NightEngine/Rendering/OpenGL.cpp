#include "OpenGL.h"
#include "../Debugging/Macros.h"
#include <math.h>

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

	ProjectionMatrix = glm::perspective(60.0f, (float)m_GameSettings->m_ScreenX / (float)m_GameSettings->m_ScreenY, 0.1f, 100.f);  // Create our perspective projection matrix

	float Position[3] = {0, 0, 0};
	CreateSquare();
//	CreateSquare(2, Position);
}

void OpenGLContext::ReshapeWindow( unsigned x, unsigned y )
{
	m_GameSettings->m_ScreenX = x; // Set the window width
	m_GameSettings->m_ScreenY = y; // Set the window height
	ProjectionMatrix = glm::perspective(60.0f, (float)m_GameSettings->m_ScreenX / (float)m_GameSettings->m_ScreenY, 0.1f, 100.f);  // Create our perspective projection matrix
	if (bSceneReady) RenderScene();
}

void OpenGLContext::RenderScene() {
	// @TODO: there was a comment that said we only need to call glViewport when resizing a window.
	glViewport(0, 0, m_GameSettings->m_ScreenX, m_GameSettings->m_ScreenY); // Set the viewport size to fill the window
	PrintErrors();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers
	PrintErrors();

	ViewMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, -5.f)); // Create our view matrix which will translate us back 5 units
	ModelMatrix = glm::scale(mat4(1.0f), vec3(0.5f));  // Create our model matrix which will halve the size of our model

	m_Shader->Bind();
	PrintErrors();

	int ProjectionMatrixLocation = glGetUniformLocation(m_Shader->ID(), "ProjectionMatrix"); // Get the location of our projection matrix in the shader
	int ViewMatrixLocation = glGetUniformLocation(m_Shader->ID(), "ViewMatrix"); // Get the location of our view matrix in the shader
	int ModelMatrixLocation = glGetUniformLocation(m_Shader->ID(), "ModelMatrix"); // Get the location of our model matrix in the shader
	
	glUniformMatrix4fv(ProjectionMatrixLocation, 1, GL_FALSE, &ProjectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(ViewMatrixLocation, 1, GL_FALSE, &ViewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(ModelMatrixLocation, 1, GL_FALSE, &ModelMatrix[0][0]); // Send our model matrix to the shader

	glBindVertexArray(VertexArrayObject[0]); // Bind our Vertex Array Object
	
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // Draw our square
	glBindVertexArray(0); // Unbind our Vertex Array Object

	m_Shader->Unbind();
	PrintErrors();

	SwapBuffers(m_DeviceContext); // Swap buffers so we can see our rendering
	PrintErrors();
}

// @TODO: have CreateSquare take in a size parameter
void OpenGLContext::CreateSquare() 
{
	// @TODO: change these new calls
	// @TODO: add a fourth variable per vertex so we can add the "see through" color option
	float* Vertices = new float[12];
	float* Colors = new float[12];

	Vertices[0] = -0.5; Vertices[1] = 0.5; Vertices[2] = 0.0; // Top left corner
	Colors[0] = 1; Colors[1] = 1; Colors[2] = 1; 

	Vertices[3] = -0.5; Vertices[4] = -0.5; Vertices[5] = 0.0; // Bottom left corner
	Colors[3] = 1; Colors[4] = 1; Colors[5] = 1; 

	Vertices[6] = 0.5; Vertices[7] = 0.5; Vertices[8] = 0.0; // Top Right corner
	Colors[6] = 1; Colors[7] = 1; Colors[8] = 1; 

	Vertices[9] = 0.5; Vertices[10] = -0.5; Vertices[11] = 0.0; // Bottom right corner
	Colors[9] = 1; Colors[10] = 1; Colors[11] = 1; 


	glGenVertexArrays(1, &VertexArrayObject[0]); // Create our Vertex Array Object
	glBindVertexArray(VertexArrayObject[0]); // Bind our Vertex Array Object so we can use it

	glGenBuffers(2, VertexBufferObject); // Generate two Vertex Buffer Objects

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), Vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[0]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), Vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our second vertex attributes pointer

	glEnableVertexAttribArray(0); // Enable the first vertex attribute array
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array
	glBindVertexArray(0); // 
	PrintErrors();

	delete [] Vertices;
	delete [] Colors;
}

void OpenGLContext::CreateSquare(float SideLength, float Position[3]) 
{
	// @TODO: change this new call
	float* Vertices = new float[18];

	assert (SideLength > 0);
	float HalfLength = SideLength/2;

	Vertices[0] = Position[0] - HalfLength; Vertices[1] = Position[1] + HalfLength; Vertices[2] = Position[2]; // Bottom left corner
	Vertices[3] = Position[0] - HalfLength; Vertices[4] = Position[1] - HalfLength; Vertices[5] = Position[2]; // Top left corner
	Vertices[6] = Position[0] + HalfLength; Vertices[7] = Position[1] + HalfLength; Vertices[8] = Position[2]; // Top Right corner
	Vertices[9] = Position[0] + HalfLength; Vertices[10] = Position[1] - HalfLength; Vertices[11] = Position[2]; // Bottom right corner

	glGenVertexArrays(1, &VertexArrayObject[0]); // Create our Vertex Array Object
	glBindVertexArray(VertexArrayObject[0]); // Bind our Vertex Array Object so we can use it

	glGenBuffers(1, VertexBufferObject); // Generate our Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[0]); // Bind our Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), Vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

	glEnableVertexAttribArray(0); // 
	glBindVertexArray(0); // 
	PrintErrors();


	delete [] Vertices;
}

void OpenGLContext::PrintErrors()
{
	GLenum Error = glGetError();
	if( Error != GL_NO_ERROR )
	{
		DEBUG_PRINT("OpenGL Error: " << gluErrorString(Error) << "\n")
	}
}
