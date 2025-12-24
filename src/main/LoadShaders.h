#pragma once
#include <GL/glew.h>

typedef struct {
	GLenum type;
	const char* filename;
} ShaderInfo;

GLuint LoadShaders(const ShaderInfo* shaders);

