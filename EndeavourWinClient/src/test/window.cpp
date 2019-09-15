#include "window.h"

#include "../shaders/shader.h"
#include "../textures/texture.h"
#include "cube.h"
#include "skybox.h"

#define VERTEX_SHADER_PATH "src/shaders/shader.vert"
#define FRAGMENT_SHADER_PATH "src/shaders/shader.frag"
#define SKYBOX_VERTEX_SHADER_PATH "src/shaders/skybox.vert"
#define SKYBOX_FRAG_SHADER_PATH "src/shaders/skybox.frag"
#define TEXTURED_VERTEX_SHADER_PATH "src/shaders/textured_shader.vert"
#define TEXTURED_FRAGMENT_SHADER_PATH "src/shaders/textured_shader.frag"

#define TEST_TEXTURE "src/textures/general/test.png"

GLFWwindow* gameWindow;


Cube* cube;
Skybox* skybox;
GLuint shaderProgram;
GLuint skyboxShaderProgram;
GLuint texturedProgram;
GLfloat deltaTime;

GLuint testTexture;

// TODO: these values should be moved out to player class
glm::mat4 Window::P;
glm::mat4 Window::V;
glm::vec3 CamPos(0.0f, 0.0f, 20.0f);	// e  | Position of camera
glm::vec3 CamLookAt(0.0f, 0.0f, -1.0f);	// d  | This is where the camera looks at
glm::vec3 CamUp(0.0f, 1.0f, 0.0f);		// up | What orientation "up" is

GLfloat yaw = -90;
GLfloat pitch = 0;

GLfloat lastX, lastY;

int Window::Width;
int Window::Height;




void Window::CleanUp() {
	glfwDestroyWindow(gameWindow);
	glfwTerminate();

	delete(cube);
	delete(skybox);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyboxShaderProgram);
	glDeleteProgram(texturedProgram);
	glDeleteTextures(1, &testTexture);
}

void Window::InitObjects() {

	shaderProgram = Shader::LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	skyboxShaderProgram = Shader::LoadShaders(SKYBOX_VERTEX_SHADER_PATH, SKYBOX_FRAG_SHADER_PATH);
	texturedProgram = Shader::LoadShaders(TEXTURED_VERTEX_SHADER_PATH, TEXTURED_FRAGMENT_SHADER_PATH);
	testTexture = Texture::LoadTexture(TEST_TEXTURE);

	cube = new Cube();
	skybox = new Skybox;
}

void Window::Loop() {
	glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	float lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(gameWindow)) {
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(texturedProgram);
		cube->Draw(texturedProgram, testTexture);
		
		glUseProgram(skyboxShaderProgram);
		skybox->Draw(skyboxShaderProgram);

		glfwPollEvents();
		glfwSwapBuffers(gameWindow);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		ProcessInput(gameWindow);
	}
}



bool Window::CanInitialize() {
	if (glfwInit()) {
		return true;
	}
	std::cerr << "Failed to initialize GLFW" << std::endl;
	auto input = getchar();
	return false;
}

GLFWwindow* Window::GenerateWindow(int width, int height, const char* title) {

	glfwWindowHint(GLFW_SAMPLES, 4);

	gameWindow = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!gameWindow) {
		std::cerr << "Failed to open GLFW window." << std::endl;
		std::cerr << "Either GLFW is not installed or your graphics card does not support OpenGL" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	lastX = width / 2.f;
	lastY = height / 2.f;

	glfwMakeContextCurrent(gameWindow);

	// VSync
	glfwSwapInterval(1);

	glfwGetFramebufferSize(gameWindow, &width, &height);

	Window::ResizeCallback(gameWindow, width, height);
	
	return gameWindow;
	
}

void Window::PrintVersion() {

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Supported GLSL version is " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

bool Window::SetupGlew() {
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		auto input = getchar();
		glfwTerminate();
		return false;
	}
	return true;
}

bool Window::SetupOpenGL() {
	if (!SetupGlew()) {
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	return true;
}

void Window::SetupCallbacks() {
	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(gameWindow, KeyCallback);
	glfwSetMouseButtonCallback(gameWindow, MouseButtonCallback);
	glfwSetFramebufferSizeCallback(gameWindow, ResizeCallback);
	glfwSetScrollCallback(gameWindow, ScrollCallback);
	glfwSetCursorPosCallback(gameWindow, MouseCallback);
}

void Window::ErrorCallback(int error, const char* description) {
	std::cerr << description << std::endl;
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(gameWindow, GL_TRUE);
				break;

			default:
				break;
		}
	}
}

void Window::ProcessInput(GLFWwindow* window) {
	auto cameraSpeed = 10.f * deltaTime;
	bool mod = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		CamPos += cameraSpeed * CamLookAt;
		mod = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		CamPos -= cameraSpeed * CamLookAt;
		mod = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		CamPos -= glm::normalize(glm::cross(CamLookAt, CamUp)) * cameraSpeed;
		mod = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		CamPos += glm::normalize(glm::cross(CamLookAt, CamUp)) * cameraSpeed;
		mod = true;
	}

	if (mod) {
		V = glm::lookAt(CamPos, CamPos + CamLookAt, CamUp);
	}
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {}

bool firstMouse = true;

void Window::MouseCallback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 2.4f * deltaTime;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	CamLookAt = glm::normalize(front);
	V = glm::lookAt(CamPos, CamPos + CamLookAt, CamUp);
}

void Window::ResizeCallback(GLFWwindow* window, int width, int height) {

	Window::Width = width;
	Window::Height = height;

	glViewport(0, 0, width, height);

	if (height > 0) {
		P = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 5000.0f);
		V = glm::lookAt(CamPos, CamPos + CamLookAt, CamUp);
	}

}

void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {}
