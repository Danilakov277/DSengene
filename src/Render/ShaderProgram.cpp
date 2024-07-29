#include "ShaderProgram.h"

#include <iostream>
namespace Renderer {

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if(createShader(vertexShader, GL_VERTEX_SHADER,vertexShaderID));
		{
			std::cerr << "VERTEX_SHADER compile time error" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID));
		{
			std::cerr << "FRAGMENT_SHADER compile time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link time error;\n" << infolog << std::endl;
			
		}
		else
		{
			is_compiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(ID);
	}

	bool ShaderProgram::use() const
	{
		glUseProgram(ID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(ID);
		ID = shaderProgram.ID;
		is_compiled = shaderProgram.is_compiled;

		shaderProgram.ID = 0;
		shaderProgram.is_compiled = false;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		ID = shaderProgram.ID;
		is_compiled = shaderProgram.is_compiled;

		shaderProgram.ID = 0;
		shaderProgram.is_compiled = false;
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success; 
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infolog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr,infolog);
			std::cerr << "ERROR::SHADER: Compile time error;\n" << infolog << std::endl;
			return false;
		}
		return true;
	}
}