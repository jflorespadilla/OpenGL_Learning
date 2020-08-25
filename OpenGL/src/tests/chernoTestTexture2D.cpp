#include "chernoTestTexture2D.h"

#include "imgui/imgui.h"

namespace test {
	ChernoTestTexture2D::ChernoTestTexture2D() 
        : m_Proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
          m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
          m_TranslationA(0.50f, 0.50f, 0.0f),
          m_TranslationB(1.0f, 1.0f, 0.0f)
          
    {
        float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indicies[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_Shader = std::make_unique<Shader>("res/shaders/basic.shader");
        m_VAO = std::make_unique<VertexArray>();

        m_VB = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        m_VAO->addBuffer(*m_VB, layout);

        m_IB = std::make_unique<IndexBuffer>(indicies, 6);

        m_Shader->bind();
        m_Texture = std::make_unique<Texture>("res/textures/druids.jpg");
	}

	ChernoTestTexture2D::~ChernoTestTexture2D() {

	}

	void ChernoTestTexture2D::onUpdate(float deltaTime) {

	}

	void ChernoTestTexture2D::onRender() {

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_IB, *m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->bind();
            m_Shader->setUniformMat4f("u_MVP", mvp);
            renderer.draw(*m_VAO, *m_IB, *m_Shader);
        }

	}

	void ChernoTestTexture2D::onImguiRender() {
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 1.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 1.0f);
	}
}