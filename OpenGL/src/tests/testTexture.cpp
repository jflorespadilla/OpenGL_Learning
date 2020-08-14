#include "testTexture.h"
#include "imgui/imgui.h"

namespace test {

	TestTexture::TestTexture() {
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));
		vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));
		layout.push<float>(2);
		layout.push<float>(2);
		va.addBuffer(*vb, layout);
		ib = new IndexBuffer(indicies, 6);
		shader = new Shader("res/shaders/basic.shader");
		shader->bind();
		texture = new Texture("res/textures/rainbow.png");
		texture->bind();
		shader->setUniform1i("u_Texture", 0);
		va.unbind();
		vb->unbind();
		ib->unbind();
		shader->unbind();
		translationA = glm::vec3(0.50f, 0.50f, 0.0f);
		translationB = glm::vec3(1.0f, 1.0f, 0.0f);
	}

	TestTexture::~TestTexture() {
		delete vb;
		delete ib;
		delete shader;
		delete texture;

		vb = NULL;
		ib = NULL;
		shader = NULL;
		texture = NULL;
	}

	void TestTexture::onUpdate(float deltaTime) {

	}

	void TestTexture::onRender() {
		renderer.clear();
		shader->bind();
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(va, *ib, *shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;
			shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(va, *ib, *shader);
		}
	}

	void TestTexture::onImguiRender() {
		ImGui::SliderFloat3("Translation A", &translationA.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Translation B", &translationB.x, -1.0f, 1.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}