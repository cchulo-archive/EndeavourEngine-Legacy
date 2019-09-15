#pragma once

#include "quad.h"



class Cube {

private:
	glm::mat4 toWorld;
	
	Quad* front;
	Quad* back;
	Quad* left;
	Quad* right;
	Quad* bottom;
	Quad* top;

public:
	Cube();
	~Cube();

	

	void Draw(GLuint, GLuint);

};
