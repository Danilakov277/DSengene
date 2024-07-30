#pragma once

#include <iostream>
#include <string>
#include<memory>
#include <map>

namespace Renderer
{
	class ShaderProgram;
}
class ResourceManger
{
public:
	ResourceManger(const std::string& executablePath);
	~ResourceManger() = default;

	ResourceManger(const ResourceManger&) = delete;
	ResourceManger& operator = (const ResourceManger&) = delete;
	ResourceManger& operator = (ResourceManger&&) = delete;
	ResourceManger(ResourceManger&&) = delete;

	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:
	std::string getFileString(const std::string& relatveFilePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_shaderProgram;

	std::string m_path;

};