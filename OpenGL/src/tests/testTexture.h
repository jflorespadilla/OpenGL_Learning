#pragma once

#include "test.h"
#include "renderer.h"
#include "vertexBufferLayout.h"
#include "texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {
	class TestTexture : Test {
	public:
		TestTexture();
		~TestTexture();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImguiRender() override;

	private:

		/* I'm not going to over complicate the code. I'm just going to define concrete values now.
		   I'll try making a more robust and generic test later. */

		float positions[16] = {
		 -0.5f, -0.5f, 0.0f, 0.0f,
		  0.5f, -0.5f, 1.0f, 0.0f,
		  0.5f, 0.5f, 1.0f, 1.0f,
		 -0.5f, 0.5f, 0.0f, 1.0f 
		};

		unsigned int indicies[6] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		VertexArray va;
		VertexBuffer* vb;
		VertexBufferLayout layout;
		IndexBuffer* ib;
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);;
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		Shader* shader;
		Texture* texture;
		Renderer renderer;
		glm::vec3 translationA;
		glm::vec3 translationB;
	};
}