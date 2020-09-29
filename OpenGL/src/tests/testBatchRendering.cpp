#include "testBatchRendering.h"

#include "imgui/imgui.h"

namespace test {
    TestBatchRendering::TestBatchRendering()  {
		// Initialize all relevant arrays of positions, indicies, and verticies

		// Pre-log push
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		// Pass information to buffers

		// Bind buffers

		// No code update, reading being done...
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