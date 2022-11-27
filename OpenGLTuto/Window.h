#ifndef WINDOW_H

#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/*****************/
// Constante
const float WIDTH	= 800;
const float HEIGHT	= 600;

class Window
{
public:
	Window();
	~Window();
	GLFWwindow* CreateWindow();
	bool InitGlad();
};


#endif