#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>

#include "shader.h"

class Shader {
public:
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
};
