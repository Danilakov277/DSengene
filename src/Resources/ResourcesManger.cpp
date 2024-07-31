#include "ResourcesManger.h"

#include "../Render/ShaderProgram.h"

#include "../Render/Texture2D.h"

#include "../Render/Sprite.h"

#include<sstream>
#include<fstream>
#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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

std::shared_ptr<Renderer::Texture2D> ResourceManger::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int widht = 0;
	int hight = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &widht, &hight, &channels, 0);
	if (!pixels)
	{
		std::cerr << "cant load image: " << texturePath << std::endl;
		return nullptr; 
	}

	std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<Renderer::Texture2D>(widht,
																															hight,
																															pixels,
																															channels,
																															GL_NEAREST,
																															GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManger::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program:" << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceManger::loadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Cant find the sprite texture:" << textureName << std::endl;
	}
	auto pShader = getShaderProgram(shaderName);
	if (!pShader)
	{
		std::cerr << "Cant find the sprite shader:" << shaderName << std::endl;
	}
	std::shared_ptr<Renderer::Sprite> newSprite = m_sprites.emplace(spriteName, std::make_shared<Renderer::Sprite>(pTexture,
		pShader,
		glm::vec2(0.0f,0.0f),
		glm::vec2(spriteWidth,spriteHeight),
		0)).first->second;

	return newSprite;
}

std::shared_ptr<Renderer::Sprite> ResourceManger::getSprite(const std::string& spriteName)
{
	SpriteMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the sprite:" << spriteName << std::endl;
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
