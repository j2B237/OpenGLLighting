#ifndef SHADER_H

#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();
	void Use();
	void SetMat4(const std::string& name, glm::mat4 mat);
	void SetFloat(const std::string& name, float val);
	void SetInt(const std::string& name, int val);
	void SetVec3(const std::string& name, float x, float y, float z);
	
private:

	GLint CreateShaderFromSrc(const char* shaderPath, GLenum type);
	std::string LoadShaderFromSrc(const char* filename);

};


#endif

