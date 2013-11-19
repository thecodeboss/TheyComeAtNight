#include "Mesh.h"
#include <cstring>

Mesh* Mesh::CreateCube()
{
	Mesh* mesh = new Mesh();
	mesh->m_NumVertices = CubeNumVertices;
	mesh->m_NumTriangles = CubeNumTriangles;
	mesh->m_Vertices = new float[3*CubeNumVertices];
	mesh->m_VertexIndices = new unsigned[3*CubeNumTriangles];
	mesh->m_TextureCoordinates = new float[2*CubeNumVertices];
	mesh->m_VertexColours = new float[4*CubeNumVertices];

	memcpy((void *)mesh->m_Vertices, (void *)&CubeVertices[0][0], 3*sizeof(float)*CubeNumVertices);
	memcpy((void *)mesh->m_VertexIndices, (void *)&CubeIndices[0], 3*sizeof(unsigned)*CubeNumTriangles);
	memcpy((void *)mesh->m_TextureCoordinates, (void *)&CubeTextureCoordinates[0], 2*sizeof(float)*CubeNumVertices);
	memcpy((void *)mesh->m_VertexColours, (void *)&CubeDefaultColours[0][0], 4*sizeof(float)*CubeNumVertices);

	return mesh;
}
