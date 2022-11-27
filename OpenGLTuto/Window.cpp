#include "Window.h"

Window::Window()
{
	// Constructor
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n";
	}
	else
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	}
}

/**************************/
Window::~Window(){}		// Destructor

/**************************/

GLFWwindow* Window::CreateWindow()
{
	return glfwCreateWindow(WIDTH, HEIGHT, "Tutorial", NULL, NULL);
}

/************************/
bool Window::InitGlad()
{
	if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		return false;
	}
	return true;
}

/*************************/
