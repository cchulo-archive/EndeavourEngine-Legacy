#pragma once

#include <glm/mat4x4.hpp>

class Camera {
public:
	glm::vec3 CamPos;
	glm::vec3 CamLookAt;
	glm::vec3 CamUp;

	Camera();
	~Camera();
};