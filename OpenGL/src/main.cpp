#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

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

        Shader shader("res/shaders/basic.shader");
        shader.bind();
        shader.setUniform4f("u_Color", 0.2f, 0.5f, 0.8, 1.0f);

        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        // Values used to change the color of my rectangle
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float increment = 0.02f;

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_Color", r, g, b, 1.0f);

            renderer.draw(va, ib, shader);

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
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}