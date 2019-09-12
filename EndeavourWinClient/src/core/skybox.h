#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

class Skybox {
public:
	Skybox();
	~Skybox();

	const GLfloat vertices[8][3] = {
		// "Front" vertices
		{ -1000.0, -1000.0,  -1000.0 },{ 1000.0, -1000.0,  -1000.0 },{ 1000.0,  1000.0,  -1000.0 },{ -1000.0,  1000.0,  -1000.0 },
		// "Back" vertices
		{ -1000.0, -1000.0, 1000.0 },{ 1000.0, -1000.0, 1000.0 },{ 1000.0,  1000.0, 1000.0 },{ -1000.0,  1000.0, 1000.0 }
	};

	const GLuint indices[6][6] = {
		// Front face
		{ 0, 1, 2, 2, 3, 0 },
		// Top face
		{ 4, 0, 3, 3, 7, 4 },

		// Back face
		{ 7, 6, 5, 5, 4, 7 },
		// Bottom face
		{ 1, 5, 6, 6, 2, 1 },
		// Left face
		{ 4, 5, 1, 1, 0, 4 },
		// Right face
		{ 3, 2, 6, 6, 7, 3 }
	};


	glm::mat4 toWorld;
	GLuint VBO, VAO, EBO;
	GLuint uProjection, uModelview, cubemapTexture;

	const std::vector<std::string> faceTextures =
	{
		"resources/ashcanyon_rt.ppm",
		"resources/ashcanyon_lf.ppm",
		"resources/ashcanyon_up.ppm",
		"resources/ashcanyon_dn.ppm",
		"resources/ashcanyon_bk.ppm",
		"resources/ashcanyon_ft.ppm",
	};

	void draw(GLuint);
	unsigned char* loadPPM(const char* filename, int& width, int& height);
	GLuint loadCubemap();

};