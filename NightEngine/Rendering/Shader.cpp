#include "Shader.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <streambuf>
#include "../Debugging/Macros.h"

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

string ReadFile(const char * Filename)
{
	ifstream t(Filename);
	if (!t.is_open()) DEBUG_PRINT("Failed to open file")
	string str;

	t.seekg(0, ios::end);
	str.reserve(t.tellg());
	t.seekg(0, ios::beg);

	str.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	return str;
}

bool Shader::Initialize(const char *VertexShaderFile, const char *FragmentShaderFile) {

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	string temp = ReadFile(VertexShaderFile);
	const char *VertexShaderText = temp.c_str();

	string temp2 = ReadFile(FragmentShaderFile);
	const char *FragmentShaderText = temp2.c_str();

	CHECKPOINTER(VertexShaderText, "Vertex Shader file not found.\n")
	CHECKPOINTER(FragmentShaderText, "Fragment Shader file not found.\n")

	glShaderSource(VertexShader, 1, &VertexShaderText, 0);
	glShaderSource(FragmentShader, 1, &FragmentShaderText, 0);

	glCompileShader(VertexShader);
	PrintLog(VertexShader);

	glCompileShader(FragmentShader);
	PrintLog(FragmentShader);

	ShaderID = glCreateProgram();
	glAttachShader(ShaderID, VertexShader);
	glAttachShader(ShaderID, FragmentShader);
	glLinkProgram(ShaderID);

	glBindAttribLocation(ShaderID, 0, "in_Position"); // Bind a constant attribute location for positions of vertices
	glBindAttribLocation(ShaderID, 1, "in_Color"); // Bind another constant attribute location, this time for color

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

void Shader::PrintLog(GLuint obj)
{
	int infologLength = 0;
	int maxLength = 1000;

	if(glIsShader(obj))
		glGetShaderiv(obj,GL_INFO_LOG_LENGTH,&maxLength);
	else
		glGetProgramiv(obj,GL_INFO_LOG_LENGTH,&maxLength);

	char infoLog[1000];

	if (glIsShader(obj))
		glGetShaderInfoLog(obj, maxLength, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, maxLength, &infologLength, infoLog);

	if (infologLength > 0)
		DEBUG_PRINT(infoLog << "\n");
}
