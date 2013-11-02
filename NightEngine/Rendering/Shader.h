#ifndef Shader_h__
#define Shader_h__

#include <stdlib.h>
#include "OpenGL.h"

//#include <string>

class Shader {
public:
	Shader();
	Shader(const char *VertexShaderFile, const char *FragmentShaderFile);
	bool Initialize(const char *VertexShaderFile, const char *FragmentShaderFile);
	~Shader();
	void Bind();
	void Unbind();
	unsigned ID();
private:
	unsigned ShaderID;
	unsigned FragmentShader;
	unsigned VertexShader;
};

#endif // Shader_h__
