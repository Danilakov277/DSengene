#include "ResourcesManger.h"
#include "../Render/ShaderProgram.h"

#include<sstream>
#include<fstream>
#include<iostream>

ResourceManger::ResourceManger(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManger::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "NO Vertex shader!" << std::endl;
		return nullptr;
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "NO fragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderProgram.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->IsCompiled())
	{
		return newShader;
	}

	std::cerr << "cant load shader program:\n"
		<< "Vertex:" << vertexPath << "\n"
		<< "fragment:" << fragmentPath << "\n" << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManger::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramMap::const_iterator it = m_shaderProgram.find(shaderName);
	if (it != m_shaderProgram.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program:" << shaderName << std::endl;
	return nullptr; 
}

std::string ResourceManger::getFileString(const std::string& relatveFilePath) const
{
	std::ifstream f;
	f.open(m_path + "/" + relatveFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to open file: " << relatveFilePath << std::endl;
		return std::string{};
	}
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
