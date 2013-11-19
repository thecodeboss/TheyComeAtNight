#ifndef Mesh_h__
#define Mesh_h__

#include "Models/Cube.h"

class Mesh
{

public:

	unsigned m_NumVertices;
	unsigned m_NumTriangles;
	float* m_Vertices;
	unsigned* m_VertexIndices;
	float* m_TextureCoordinates;
	float* m_VertexColours;

	static Mesh* CreateCube();

};

#endif // Mesh_h__
