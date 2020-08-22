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
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "tests/test.h"
#include "tests/testClearColor.h"
#include "tests/testTexture.h"

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);
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
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();

        test::Test* CurrentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(CurrentTest);
        CurrentTest = testMenu;

        testMenu->registerTest<test::TestClearColor>("Clear Color");
        testMenu->registerTest<test::TestTexture>("Test Texture");

        while (!glfwWindowShouldClose(window)) {

            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (CurrentTest) {
                CurrentTest->onUpdate(0.0f);
                CurrentTest->onRender();

                ImGui::Begin("Test");
                if (CurrentTest != testMenu && ImGui::Button("<-")) {
                    delete CurrentTest;
                    CurrentTest = testMenu;
                }
                CurrentTest->onImguiRender();
                ImGui::End();
            }

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        delete CurrentTest;
        if (CurrentTest != testMenu) {
            delete testMenu;
        }
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}