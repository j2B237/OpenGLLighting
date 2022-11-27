#include "Vertex.h"

/*************************/

Vertex::Vertex()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
}

/*************************/

Vertex::~Vertex(){}

/***************************/
void Vertex::DeleteBuffers()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
