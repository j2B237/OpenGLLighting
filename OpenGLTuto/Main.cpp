#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"
#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"
#include "Transformation.h"

/********************************/

void frameBufferCallback(GLFWwindow* window, int width, int height);
void mouse_scrollCallback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

/*******************************/

// Transform object in 3D
Transformation transform;

/******************************/
int main(int argc, char* argv[])
{
	Window window;
	GLFWwindow* win = window.CreateWindow();

	if (win == NULL)
	{
		std::cout << "Failed to create a window\n";
		glfwTerminate();
		return -1;
	}
	else
	{
		glfwMakeContextCurrent(win);
		glfwSetFramebufferSizeCallback(win, frameBufferCallback);

		glfwSetCursorPosCallback(win, mouse_scrollCallback);
		glfwSetScrollCallback(win, scroll_callback);

		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!window.InitGlad())
		{
			std::cout << "Failed to load pointer functions\n";
			return -1;
		}

		glEnable(GL_DEPTH_TEST);
	}

	// Load shader
	Shader cubeShader("Assets/cube_vertex.glsl", "Assets/cube_fragment.glsl");
	Shader lightShader("Assets/light_vertex.glsl", "Assets/light_fragment.glsl");

	// Create Vertex Buffer objects

	/*													+Y
	*       V7---------V4								^     * +Z
	       / |        / |								|	 /
		  /  |       /  |								|   /
		V3---|------V0  |								|  /
		 |  V6------|---V5								| /
		 |  /       |  /				<--------------- ---------------> +X
		V2 ---------V1								   /|
													  /	|
													 /	|
													/	|
												   /	*
												  /
												(-Z)
	*/

	// TODO : Phong lighting model { Ambient, diffuse, spectacular lighting }

	GLfloat vertices[] =
	{
		// Position				// Normals				// Texture coord
		-0.5f, -0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		0.0f, 0.0f,				//V2	--
		 0.5f, -0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		1.0f, 0.0f,				//V1	  |
		 0.5f,  0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		1.0f, 1.0f,				//V0	  |
		 0.5f,  0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		1.0f, 1.0f,				//V0      |	--> Face (V2, V1, V0, V3)
		-0.5f,  0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		0.0f, 1.0f,				//V3      |
		-0.5f, -0.5f, -0.5f,  /*0.0f,  0.0f, -1.0f,*/		0.0f, 0.0f,				//V2	--

		-0.5f, -0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		0.0f, 0.0f,				//V6	--
		 0.5f, -0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		1.0f, 0.0f,				//V5	  |
		 0.5f,  0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		1.0f, 1.0f,				//V4	  |
		 0.5f,  0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		1.0f, 1.0f,				//V4	  | --> Face (V6, V5, V4, V7)
		-0.5f,  0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		0.0f, 1.0f,				//V7      |
		-0.5f, -0.5f,  0.5f,  /*0.0f,  0.0f, 1.0f,*/		0.0f, 0.0f,				//V6	--

		-0.5f,  0.5f,  0.5f, /*-1.0f,  0.0f,  0.0f,*/		1.0f, 0.0f,				//V7	--
		-0.5f,  0.5f, -0.5f, /*-1.0f,  0.0f,  0.0f,*/		1.0f, 1.0f,				//V3	  |
		-0.5f, -0.5f, -0.5f, /*-1.0f,  0.0f,  0.0f,*/		0.0f, 1.0f,				//V2	  |
		-0.5f, -0.5f, -0.5f, /*-1.0f,  0.0f,  0.0f,*/		0.0f, 1.0f,				//V2	  | --> Face (V7, V3, V2, V6)
		-0.5f, -0.5f,  0.5f, /*-1.0f,  0.0f,  0.0f,*/		0.0f, 0.0f,				//V6	  |
		-0.5f,  0.5f,  0.5f, /*-1.0f,  0.0f,  0.0f,*/		1.0f, 0.0f,				//V7	--

		 0.5f,  0.5f,  0.5f,  /*1.0f,  0.0f,  0.0f,*/		1.0f, 0.0f,				//V4	--
		 0.5f,  0.5f, -0.5f,  /*1.0f,  0.0f,  0.0f,*/		1.0f, 1.0f,				//V0	  |
		 0.5f, -0.5f, -0.5f,  /*1.0f,  0.0f,  0.0f,*/		0.0f, 1.0f,				//V1	  |
		 0.5f, -0.5f, -0.5f,  /*1.0f,  0.0f,  0.0f,*/		0.0f, 1.0f,				//V1	  | --> Face (V4, V0, V1, V5)
		 0.5f, -0.5f,  0.5f,  /*1.0f,  0.0f,  0.0f,*/		0.0f, 0.0f,				//V5	  |
		 0.5f,  0.5f,  0.5f,  /*1.0f,  0.0f,  0.0f,*/		1.0f, 0.0f,				//V4	--

		-0.5f, -0.5f, -0.5f,  /*0.0f, -1.0f,  0.0f,*/		0.0f, 1.0f,				//V2	--
		 0.5f, -0.5f, -0.5f,  /*0.0f, -1.0f,  0.0f,*/		1.0f, 1.0f,				//V1	  |
		 0.5f, -0.5f,  0.5f,  /*0.0f, -1.0f,  0.0f,*/		1.0f, 0.0f,				//V5	  |
		 0.5f, -0.5f,  0.5f,  /*0.0f, -1.0f,  0.0f,*/		1.0f, 0.0f,				//V5	  | --> Face (V2, V1, V5, V6)
		-0.5f, -0.5f,  0.5f,  /*0.0f, -1.0f,  0.0f,*/		0.0f, 0.0f,				//V6	  |
		-0.5f, -0.5f, -0.5f,  /*0.0f, -1.0f,  0.0f,*/		0.0f, 1.0f,				//V2	--

		-0.5f,  0.5f, -0.5f,  /*0.0f,  1.0f,  0.0f,*/		0.0f, 1.0f,				//V3	--
		 0.5f,  0.5f, -0.5f,  /*0.0f,  1.0f,  0.0f,*/		1.0f, 1.0f,				//V0	  |
		 0.5f,  0.5f,  0.5f,  /*0.0f,  1.0f,  0.0f,*/		1.0f, 0.0f,				//V4	  |
		 0.5f,  0.5f,  0.5f,  /*0.0f,  1.0f,  0.0f,*/		1.0f, 0.0f,				//V4	  | --> Face (V3, V0, V4, V7)
		-0.5f,  0.5f,  0.5f,  /*0.0f,  1.0f,  0.0f,*/		0.0f, 0.0f,				//V7	  |
		-0.5f,  0.5f, -0.5f,  /*0.0f,  1.0f,  0.0f,*/		0.0f, 1.0f				//V3	--
	};

	Vertex cubeVertex;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVertex.VAO);

	// Set attributes pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Light source
	Vertex lightVertex;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(lightVertex.VAO);

	// Set attributes pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture
	Texture cubeTexture("Assets/container.jpg", GL_TEXTURE_2D, GL_REPEAT, GL_LINEAR);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 3 * sizeof(float) ));
	glEnableVertexAttribArray(1);

	// Define cube emited lighting
	cubeShader.Use();
	cubeShader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
	cubeShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);

	// Game loop
	while (!glfwWindowShouldClose(win))
	{
		float currentFrame	= (float)(glfwGetTime());
		transform.deltaTime = currentFrame - transform.lastFrame;
		transform.lastFrame = currentFrame;

		// Process input
		transform.ProcessCameraMovement(win);

		// Render stuff
		//glClearColor(0.2f, 0.7f, 0.2f, 0.6f);
		glClearColor(0.1f, 0.1f, 0.1f, 0.6f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cubeTexture.Activate(GL_TEXTURE_2D, GL_TEXTURE0);

		glm::mat4 model			= glm::mat4(1.0f);
		glm::mat4 model2		= glm::mat4(1.0f);
		glm::mat4 view			= glm::mat4(1.0f);
		glm::mat4 projection	= glm::mat4(1.0f);
		glm::vec3 lightPos		= glm::vec3(1.0f, 1.0f, 2.0f);
		

		// Transform to 3D object and draw our cube
		
		model = glm::rotate(model, float(glfwGetTime()) * glm::radians(55.0f), glm::vec3(0.0f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5));

		transform.CameraView(cubeShader, 0.1f, 100.0f, model, view, projection);
		cubeShader.Use();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Add our light source
		model2 = glm::rotate(model2, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::translate(model2, lightPos);
		model2 = glm::scale(model2, glm::vec3(0.5));

		transform.Transform3D(lightShader, 45.0f, 0.1f, 100.0f, model2, view, projection);
		glBindVertexArray(lightVertex.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Events
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
	cubeVertex.DeleteBuffers();
	lightVertex.DeleteBuffers();

	glfwTerminate();

	return EXIT_SUCCESS;
}

/***********************************/

void frameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/**********************************/

void mouse_scrollCallback(GLFWwindow* window, double xPos, double yPos)
{
	float xPosIn = static_cast<float>(xPos);
	float yPosIn = static_cast<float>(yPos);

	if (transform.firstMouse)
	{
		transform.lastX			= xPosIn;
		transform.lastY			= yPosIn;
		transform.firstMouse		= false;
	}


	float xOffset	= xPosIn - transform.lastX;
	float yOffset	= transform.lastY - yPosIn;

	transform.lastX = xPosIn;
	transform.lastY = yPosIn;

	transform.camera.ProcessMouseMovement(yOffset, xOffset);
}

/********************************/

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	transform.camera.ProcessMouseScroll(static_cast<float>(yOffset) );
}

/*******************************/