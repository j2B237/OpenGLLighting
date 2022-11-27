#include "Texture.h"

/********************************/
Texture::Texture(const char* texturePath, GLenum type, GLenum wrapParams, GLenum filterParam)
{
	glGenTextures(1, &ID);
	glBindTexture(type, ID);
	
	// Wrap texture options
	glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapParams);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapParams);

	// Filter texture options
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filterParam);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filterParam);

	unsigned char *data = LoadTextureFromSrc(texturePath, type);

	stbi_image_free(data);
}

/***************************/

Texture::~Texture(){}


/**************************/
void Texture::Activate(GLenum target, GLenum textUnit)
{
	glActiveTexture(textUnit);
	glBindTexture(target, this->ID);
}

//private

/****************************************************/
unsigned char* Texture::LoadTextureFromSrc(const char* filename, GLenum target)
{
	unsigned char *data = stbi_load(filename, &width, &height, &nChannels, 0);
	if (data)
	{
		glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(target);
	}
	else
	{
		std::cout << "Failed to open : " << filename << std::endl;
	}

	return data;
}

/*******************************************************/
