#include "Shader.h"

/**********************************************************************/

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int success;
	char infoLog[512];

	GLint vertexId = CreateShaderFromSrc(vertexShaderPath, GL_VERTEX_SHADER);
	GLint fragmentId = CreateShaderFromSrc(fragmentShaderPath, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();

	glAttachShader(ID, vertexId);
	glAttachShader(ID, fragmentId);

	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader program error : " << infoLog << std::endl;
	}
}

/*******************************************************************/
Shader::~Shader(){}

/*********************************************************************/
void Shader::Use()
{
	glUseProgram(ID);
}

/*******************************************************************/

void Shader::SetMat4(const std::string& name, glm::mat4 mat)
{
	GLint location = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat) );
}

/********************************************************************/

void Shader::SetFloat(const std::string& name, float val)
{
	GLint location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, val);
}

/*******************************************************************/
void Shader::SetInt(const std::string& name, int val)
{
	GLint location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, val);
}

/*******************************************************************/
void Shader::SetVec3(const std::string& name, float x, float y, float z)
{
	GLint location = glGetUniformLocation(ID, name.c_str());
	glUniform3f(location, x, y, z);
}

/************************************************************/
// private

GLint Shader::CreateShaderFromSrc(const char* shaderPath, GLenum type)
{
	int success;
	char infoLog[512];

	GLint id = glCreateShader(type);

	std::string shaderSrc = LoadShaderFromSrc(shaderPath);
	const GLchar* shader = shaderSrc.c_str();

	glShaderSource(id, 1, &shader, NULL);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "Shader Error : " << infoLog << std::endl;
	}

	return id;

}

/*********************************************************/

std::string Shader::LoadShaderFromSrc(const char* filename)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string rep = "";

	file.open(filename);

	if (file.is_open())
	{
		buffer << file.rdbuf();
		rep = buffer.str();
	}
	else
	{
		std::cout << "Can't open file :" << filename << std::endl;
	}
	file.close();

	return rep;
}

/************************************************************/