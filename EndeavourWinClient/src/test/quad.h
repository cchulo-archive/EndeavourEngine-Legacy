#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class Quad {
private:
	const GLfloat vertices[8][3] = {
		// Front vertices
		{ -0.5, -0.5,  0.5 }, // 0
		{  0.5, -0.5,  0.5 }, // 1
		{  0.5,  0.5,  0.5 }, // 2
		{ -0.5,  0.5,  0.5 }, // 3
	};

	const GLuint indices[1][6] = {
		{ 0, 1, 2, 2, 3, 0 },
	};

	const GLfloat uvs[4][2] = {
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 0 },
		{ 0, 0 }
	};

	GLuint VBO, VAO, EBO, UVBO;

	glm::mat4 toWorld;

public:
	Quad();
	~Quad();

	void Draw(GLuint, GLuint, glm::mat4, glm::mat4);
};
