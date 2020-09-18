#pragma once

#include "test.h"

#include "renderer.h"
#include "vertexBufferLayout.h"
#include "texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {
	class TestBatchRendering : public Test {
	public:
		TestBatchRendering();
		~TestBatchRendering();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImguiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IB;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VB;

		glm::mat4 m_Proj, m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
}