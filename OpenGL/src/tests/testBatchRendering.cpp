#include "testBatchRendering.h"

#include "imgui/imgui.h"

namespace test {
    TestBatchRendering::TestBatchRendering() 
		: m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
		m_TranslationA(0.50f, 0.50f, 0.0f),
		m_TranslationB(1.0f, 1.0f, 0.0f)
	{

		// Downloading Cherno's base library and will continue work from there.
		// Will attempt to update this project later once I know more or less
		// how to properly update this project.

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
	}

    TestBatchRendering::~TestBatchRendering() {

	}

	void TestBatchRendering::onUpdate(float deltaTime) {

	}

	void TestBatchRendering::onRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestBatchRendering::onImguiRender() {

	}
}