#ifndef Model_h__
#define Model_h__

#include "Mesh.h"
#include "Texture.h"
#include "GL.h"

class Model
{
public:
	unsigned VertexArrayObject[1];
	unsigned VertexBufferObject[3]; //three buffers, one for vertices, colour, and indices
	Mesh* m_Mesh;
	Texture* m_Texture;
	mat4 m_ModelMatrix;

	static Model* CreateCube();
	void InitializeBuffers();
};

#endif // Model_h__
