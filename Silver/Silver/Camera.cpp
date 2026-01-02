#include "Camera.h"

Camera::Camera(glm::vec3 startPos) {
	Position = startPos;
	Front = glm::vec3(0.0f, 0.05, -1.05);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f;
	Pitch = 0.0f;
	MovementSpeed = 3.0f;
	MouseSensitivity = 0.1f;
}
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}