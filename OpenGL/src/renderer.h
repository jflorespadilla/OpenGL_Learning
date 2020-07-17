#pragma once

#include <GL/glew.h>

// Error checking macros. Makes it easier to debug OpenGL
// Should be used whenver an OpenGL function is called. Probably won't though.
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);