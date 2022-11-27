#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Constants

const float ZOOM = 45.0f;
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SENSIBILITY = 0.1f;
const float SPEED = 1.0f;

// camera movemnt
enum class MOVEMENT {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera
{
public:
	
	// Camera attributes
	glm::vec3 Position_;
	glm::vec3 Front_;
	glm::vec3 WorlUp_;
	glm::vec3 Right_;
	glm::vec3 Up_;

	// euler angles
	float Pitch_;
	float Yaw_;

	// Camera options
	float Zoom_;
	float Speed_;
	float Sensibility_;
	GLboolean ConstrainPitch_ = true;


	Camera(glm::vec3 position, glm::vec3 front, float yaw, float pitch, float zoom);
	Camera();
	~Camera();
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(MOVEMENT direction, float dt);
	void ProcessMouseMovement(float yOffset, float xOffset);
	void ProcessMouseScroll(float yOffset);


private:
	
	void UpdateCameraAttrib();

};

#endif