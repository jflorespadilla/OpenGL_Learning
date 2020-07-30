#pragma once

#include <string>;
#include <unordered_map>

#include "glm/glm.hpp"

struct shaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RenderID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	int getUniformLocation(const std::string& name);
public:
	Shader(const std::string& filePath);
	~Shader();

	void bind() const;
	void unbind() const;

	// set uniforms - will need to make functions for other uniform types
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, const glm::mat4 matrix);
	int compileShader(unsigned int type, const std::string& source);
	shaderProgramSource parseShader(const std::string& filePath);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};