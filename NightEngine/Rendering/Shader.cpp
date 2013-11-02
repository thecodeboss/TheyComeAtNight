#include "Shader.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

Shader::Shader() {  
}

Shader::Shader(const char *VertexShaderFile, const char *FragmentShaderFile) {
	Initialize(VertexShaderFile, FragmentShaderFile);
}

Shader::~Shader() {// The first two, just detach our vertex shader and fragment shader from our shader project, and the final 3 just delete all of the shaders and then deletes the shader program.
	glDetachShader(ShaderID, VertexShader);
	glDetachShader(ShaderID, FragmentShader);

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	glDeleteProgram(ShaderID);
}

bool Shader::Initialize(const char *VertexShaderFile, const char *FragmentShaderFile) {

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


	FILE *FilePointer = fopen(VertexShaderFile, "r");
	fseek(FilePointer, 0, SEEK_END);
	size_t FileLength = ftell(FilePointer);
	rewind(FilePointer);

	const char *VertexShaderText = (char *)malloc(FileLength); // Check for out-of-memory errors!
	fread((void *)VertexShaderText, FileLength, 1, FilePointer);

	FilePointer = fopen(FragmentShaderFile, "r");
	fseek(FilePointer, 0, SEEK_END);
	FileLength = ftell(FilePointer);
	rewind(FilePointer);

	const char *FragmentShaderText = (char *)malloc(FileLength); // Check for out-of-memory errors!
	fread((void *)FragmentShaderText, FileLength, 1, FilePointer);

	fclose(FilePointer);

	if (VertexShaderText == nullptr || FragmentShaderText == nullptr) {
		cerr << "Either vertex shader or fragment shader file not found." << endl;
		return false;
	}

	glShaderSource(VertexShader, 1, &VertexShaderText, 0);
	glShaderSource(FragmentShader, 1, &FragmentShaderText, 0);

	glCompileShader(VertexShader);
	glCompileShader(FragmentShader);

	ShaderID = glCreateProgram();
	glAttachShader(ShaderID, VertexShader);
	glAttachShader(ShaderID, FragmentShader);
	glLinkProgram(ShaderID);

	return true; // ??
}

unsigned Shader::ID() { //This is used for when we bind our shader, or for when we want to pass variables through to our shader. 
	return ShaderID;
}

	void Shader::Bind() {// This will simply attach our shader, and anything drawn afterwards will use this shader, either until this shader is unbound or another shader is enabled. 
		glUseProgram(ShaderID);
}

	void Shader::Unbind() {// This simply binds the shader 0, which is reserved for OpenGL, and will disable our current shader. 
		glUseProgram(0);
}

