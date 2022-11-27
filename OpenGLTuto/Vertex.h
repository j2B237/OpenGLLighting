#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>


class Vertex
{
public:
	unsigned int VBO, VAO;
	Vertex();
	~Vertex();
	void DeleteBuffers();
};

#endif
