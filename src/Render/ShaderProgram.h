#pragma once

#include <glad/glad.h>
#include <string>


namespace Renderer {
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		bool IsCompiled() const { return is_compiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator = (const ShaderProgram&) = delete;
		ShaderProgram& operator = (ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;


	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool is_compiled;
		GLuint ID;
	};
}