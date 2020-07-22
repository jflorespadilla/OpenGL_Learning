#pragma once

#include <GL/glew.h>

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

// Error checking macros. Makes it easier to debug OpenGL
// Should be used whenver an OpenGL function is called. Probably won't though.
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
private:

public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear() const;
    Renderer();
    ~Renderer();
};