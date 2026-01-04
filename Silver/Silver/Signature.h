#pragma once


#include <GL/glew.h>
#include <glm/glm.hpp>

class Signature {
public:
	Signature();
	~Signature();
	void Draw(GLuint program, GLuint textureID, const glm::mat4& model);
	
private:
	GLuint VAO, VBO;
};

