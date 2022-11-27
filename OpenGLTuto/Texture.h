#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include <iostream>

#include <stb/stb_image.h>

class Texture
{
public:
	unsigned int ID;
	int width, height, nChannels;
	Texture(const char* texturePath, GLenum type, GLenum wrapParams, GLenum filterParam);
	~Texture();
	void Activate(GLenum target, GLenum textUnit);

private:
	unsigned char* LoadTextureFromSrc(const char* filename, GLenum target);

};

#endif
