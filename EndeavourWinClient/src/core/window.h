#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define GLFW_INCLUDE_GLEXT

#include "../shaders/shader.h"
#include "cube.h"



class Window
{
private:
	
	static void PrintVersion();
	static bool SetupGlew();

	static void ErrorCallback(int error, const char* description);
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ResizeCallback(GLFWwindow* window, int width, int height);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	
public:

	// TODO: these values should be moved out to player class
	static glm::mat4 P;
	static glm::mat4 V;

	// TODO: this function is temporary, will be moved to scene graph
	static void InitObjects();

	static int Width;
	static int Height;

	static bool CanInitialize();
	static void CleanUp();
	static GLFWwindow* GenerateWindow(int width, int height, const char* title);
	static void Loop();
	static void SetupCallbacks();
	static bool SetupOpenGL();
	

};

