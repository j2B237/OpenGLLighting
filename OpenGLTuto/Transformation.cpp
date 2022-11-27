#include "Transformation.h"

/***********************************/

Transformation::Transformation()
{
	glm::vec3 pos		= glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 front		= glm::vec3(0.0f, 0.0f, -1.0f);

	float yaw			= -90.0f;
	float pitch			= 0.0f;
	float zoom			= 45.0f;

	ID					= 1;
	camera				= CreateCamera(pos, front, yaw, pitch, zoom);
}

/***********************************/

Transformation::~Transformation(){}

/************************************/

void Transformation::Transform3D(Shader& shader, float zoom, float nearPlane, float farPlane, glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
	view		= glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection	= glm::perspective(glm::radians(zoom), (float)WIDTH / (float)HEIGHT, nearPlane, farPlane);

	shader.Use();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);
	shader.SetMat4("model", model);
}

/************************************/

void Transformation::CameraView(Shader& shader, float nearPlane, float farPlane, glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
	view		= camera.GetViewMatrix();
	projection	= glm::perspective(glm::radians(camera.Zoom_), (float)WIDTH / (float)HEIGHT, nearPlane, farPlane);

	shader.Use();
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);
	shader.SetMat4("model", model);
}

/**************************************/

void Transformation::ProcessCameraMovement(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(MOVEMENT::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(MOVEMENT::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(MOVEMENT::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(MOVEMENT::RIGHT, deltaTime);
}

/*************************************/
// Private
Camera Transformation::CreateCamera(glm::vec3 pos, glm::vec3 front, float yaw, float pitch, float zoom)
{
	return Camera(pos, front, yaw, pitch, zoom);
}

/**********************************/
