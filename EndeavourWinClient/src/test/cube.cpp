#include "cube.h"
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube() {
	toWorld = glm::mat4(1.0f);
	front = new Quad();
	back = new Quad();
	left = new Quad();
	right = new Quad();
	bottom = new Quad();
	top = new Quad();
}

Cube::~Cube() {
	delete front;
	delete back;
	delete left;
	delete right;
	delete bottom;
	delete top;
}

void Cube::Draw(GLuint shaderProgram, GLuint textureID) {
	front->Draw(shaderProgram, textureID, glm::mat4(1.f), glm::mat4(1.f));
	left->Draw(shaderProgram, textureID, glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)), glm::mat4(1.f));
	right->Draw(shaderProgram, textureID, glm::rotate(glm::mat4(1.f), -glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)), glm::mat4(1.f));
	back->Draw(shaderProgram, textureID, glm::rotate(glm::mat4(1.f), -glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f)), glm::mat4(1.f));
	bottom->Draw(shaderProgram, textureID, glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)), glm::mat4(1.f));
	top->Draw(shaderProgram, textureID, glm::rotate(glm::mat4(1.f), -glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f)), glm::mat4(1.f));
}
