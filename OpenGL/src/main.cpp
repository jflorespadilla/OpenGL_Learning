#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

struct shaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static shaderProgramSource parseShader(const std::string& filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }

    // Didn't know this was possible in C++
    return { ss[0].str(), ss[1].str() };
}

static unsigned int compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        // Allows for dynamic allocation on the stack rather than the heap
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
   unsigned int program = glCreateProgram();
   unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
   unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

   glAttachShader(program, vs);
   glAttachShader(program, fs);
   glLinkProgram(program);
   glValidateProgram(program);

   glDeleteShader(vs);
   glDeleteShader(fs);

   return program;
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // Setting the swap inteval on the window
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "We done failed" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            -0.5f, 0.5f,
            0.0f, 0.0f,
            0.0f, 0.5f,
            -0.5f, 0.0f
        };

        unsigned int indicies[] = {
            0, 1, 2,
            1, 0, 3
        };

        // Vertex array buffer - explicitly creating one
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        /*
           With the vertex arry buffer created, the next few buffers
           are tied to the vao. This sets up the layout of the vao and can be bound
           right before a draw call. This makes it easy to use multiple vertex array buffers
           on different pieces of geometry.

           Note - using a single vao and setting everything there is also a valid
           way of doing things.
        */
        VertexArray va;
        // Create an ID for a buffer
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        // Index buffers
        IndexBuffer ib(indicies, 6);
        unsigned int ibo;

        shaderProgramSource source = parseShader("res/shaders/basic.shader");
        // Testing that shaders loaded out properly
        std::cout << source.vertexSource << std::endl;
        std::cout << source.fragmentSource << std::endl;

        unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
        GLCall(glUseProgram(shader));

        // Using a uniform to set the color of my graphics object
        int location = glGetUniformLocation(shader, "u_Color");
        ASSERT(location != -1);
        // Note - Uniforms are per-draw calls
        GLCall(glUniform4f(location, 0.2f, 0.5f, 0.8, 1.0f));


        /* Starting vertex buffer stuff */

        // Unbind all buffers
        GLCall(glBindVertexArray(0));
        GLCall(glUseProgram(0));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

        // Values used to change the color of my rectangle
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float increment = 0.02f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            GLCall(glUseProgram(shader));
            GLCall(glUniform4f(location, r, g, b, 1.0f));

            va.bind();
            ib.bind();


            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f) {
                increment = -0.02f;
            }
            else if (r < 0.0f) {
                increment = 0.02f;
            }

            r += increment;
            g += increment * 2.0f;
            b += increment * 4.0f;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        GLCall(glDeleteProgram(shader));
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}