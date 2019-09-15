#pragma once

#include <GL/glew.h>
#include <soil.h>
#include <cstddef>

class Texture {
public:
	static GLuint LoadTexture(const char* texture_path);
};