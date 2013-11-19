#include "Model.h"

Model* Model::CreateCube()
{
	Model* model = new Model();
	model->m_Mesh = Mesh::CreateCube();
	return model;
}

void Model::InitializeBuffers()
{
	glGenVertexArrays(1, &VertexArrayObject[0]); // Create our Vertex Array Object
	glBindVertexArray(VertexArrayObject[0]); // Bind our Vertex Array Object so we can use it

	glGenBuffers(3, VertexBufferObject); // Generate three Vertex Buffer Objects

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[0]); // Bind our first Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 3 * m_Mesh->m_NumVertices * sizeof(GLfloat), m_Mesh->m_Vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

	// Colours
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject[1]); // Bind our second Vertex Buffer Object
	glBufferData(GL_ARRAY_BUFFER, 4 * m_Mesh->m_NumVertices * sizeof(GLfloat), m_Mesh->m_VertexColours, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
	glVertexAttribPointer((GLuint)1, 4, GL_FLOAT, GL_FALSE, 0, 0); // Set up our second vertex attributes pointer

	// Vertex Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VertexBufferObject[2]); // Bind our third Vertex Buffer Object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * m_Mesh->m_NumTriangles * sizeof(GLuint), m_Mesh->m_VertexIndices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
	glVertexAttribPointer((GLuint)2, 3, GL_UNSIGNED_INT, GL_FALSE, 0, 0); // Set up our third vertex attributes pointer

	glEnableVertexAttribArray(0); // Enable the first vertex attribute array
	glEnableVertexAttribArray(1); // Enable the second vertex attribute array
	glEnableVertexAttribArray(2); // Enable the third vertex attribute array
	glBindVertexArray(0);
}
