#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include  <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Camera.h"

class Transformation
{
public:

	unsigned int ID;

	bool firstMouse		= true;

	float lastX			= (float)(WIDTH) / 2.0f;
	float lastY			= (float)(HEIGHT) / 2.0f;

	// Timing
	float lastFrame		= 0.0f;
	float deltaTime		= 0.0f;


	Camera camera;

	Transformation ();
	~Transformation ();
	void Transform3D (Shader& shader, float zoom, float nearPlane, float farPlane, glm::mat4& model, glm::mat4& view, glm::mat4& projection);
	void CameraView (Shader& shader, float nearPlane, float farPlane, glm::mat4& model, glm::mat4& view, glm::mat4& projection);
	void ProcessCameraMovement (GLFWwindow* window);

private:
	Camera CreateCamera(glm::vec3 pos, glm::vec3 front, float yaw, float pitch, float zoom);

};

#endif

