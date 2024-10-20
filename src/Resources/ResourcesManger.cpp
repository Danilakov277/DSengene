#include "ResourcesManger.h"

#include "../Render/ShaderProgram.h"

#include "../Render/Texture2D.h"

#include "../Render/Sprite.h"

#include "../Render/AnimatedSprite.h"

#include<sstream>
#include<fstream>
#include<iostream>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>


#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"



 ResourceManger::ShaderProgramMap ResourceManger::m_shaderProgram;
 ResourceManger::TexturesMap ResourceManger::m_textures;
 ResourceManger::SpriteMap ResourceManger::m_sprites;
 ResourceManger::AnimatedSpriteeMap ResourceManger::m_AnimatedSprite;
 std::string ResourceManger::m_path;
 std::vector<std::vector<std::string>> ResourceManger::m_levels;


void ResourceManger::setExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManger::unloadAllResources()
{
	m_shaderProgram.clear();
	m_textures.clear();
	m_sprites.clear();
	m_AnimatedSprite.clear();
	//m_path.clear();

}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManger::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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

	std::shared_ptr<RenderEngine::ShaderProgram>& newShader = m_shaderProgram.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->IsCompiled())
	{
		return newShader;
	}

	std::cerr << "cant load shader program:\n"
		<< "Vertex:" << vertexPath << "\n"
		<< "fragment:" << fragmentPath << "\n" << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManger::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramMap::const_iterator it = m_shaderProgram.find(shaderName);
	if (it != m_shaderProgram.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program:" << shaderName << std::endl;
	return nullptr; 
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManger::loadTexture(const std::string& textureName, const std::string& texturePath)
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

	std::shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<RenderEngine::Texture2D>(widht,
																															hight,
																															pixels,
																															channels,
																															GL_NEAREST,
																															GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManger::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program:" << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManger::loadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const std::string& subTextureName)
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
	std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(pTexture, subTextureName,
		pShader)).first->second;

	return newSprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManger::getSprite(const std::string& spriteName)
{
	SpriteMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the sprite:" << spriteName << std::endl;
	return nullptr;
}

std::string ResourceManger::getFileString(const std::string& relatveFilePath)
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

std::shared_ptr<RenderEngine::Texture2D> ResourceManger::loatTextureAtlas(const std::string& textureName,
	const std::vector<std::string> subTextures,
	const std::string& texturePath,
	const unsigned int subTextureWidth,
	const unsigned int subTextureHight)
{
	auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));
	if (pTexture)
	{
		const unsigned int textureWidth = pTexture->width();
		const unsigned int textureHieght = pTexture->height();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHieght;
		for (const auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHight + 0.01f) / textureHieght);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth - 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - 0.01f) / textureHieght);
			pTexture->addSubTexture(std::move(currentSubTextureName),leftBottomUV,rightTopUV);
			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHight;
			}
		}
	}
	return pTexture;
}


std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManger::loadAnimatedSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const std::string& subTextureName)
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
	std::shared_ptr<RenderEngine::AnimatedSprite> newSprite = m_AnimatedSprite.emplace(spriteName, std::make_shared<RenderEngine::AnimatedSprite>(pTexture, subTextureName,
		pShader)).first->second;

	return newSprite;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManger::getAnimatedSprite(const std::string& spriteName)
{
	auto it = m_AnimatedSprite.find(spriteName);
	if (it != m_AnimatedSprite.end())
	{
		return it->second;
	}
	std::cerr << "Cant find animated the sprite:" << spriteName << std::endl;
	return nullptr;
}

bool ResourceManger::loadJSONResources(const std::string& JSONPath)
{
	const std::string& JSONString = getFileString(JSONPath);
	if (JSONString.empty())
	{
		std::cerr << "No JSON resources file!" << std::endl;
		return false;
	}
	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str());
	if (!parseResult)
	{
		std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) << "(" << parseResult.Offset() << ")" << std::endl;
		std::cerr << "In JSON file: " << JSONPath << std::endl;
		return false;
	}
		auto shadersIt = document.FindMember("shaders");
		if (shadersIt != document.MemberEnd())
		{
			for (const auto& currentShader : shadersIt->value.GetArray())
			{
				const std::string name = currentShader["name"].GetString();
				const std::string filePath_v = currentShader["filePath_v"].GetString();
				const std::string filePath_f = currentShader["filePath_f"].GetString();
				loadShaders(name, filePath_v, filePath_f);
			}
		}
		auto textureAtlasIT = document.FindMember("textureAtlas");
		if (textureAtlasIT != document.MemberEnd())
		{
			for (const auto& curentTextureAtlas : textureAtlasIT->value.GetArray())
			{
				const std::string name = curentTextureAtlas["name"].GetString();
				const std::string filePath = curentTextureAtlas["filePath"].GetString();
				const unsigned int width = curentTextureAtlas["width"].GetUint();
				const unsigned int height = curentTextureAtlas["height"].GetUint();
				const unsigned int subTextureWidth = curentTextureAtlas["subTextureWidth"].GetUint();
				const unsigned int subTextureHeight = curentTextureAtlas["subTextureHeight"].GetUint();
				const auto subTextureArray = curentTextureAtlas["subTexture"].GetArray();
				std::vector<std::string>subTextures;
				subTextures.reserve(subTextureArray.Size());
				for (const auto& curentSubTexture : subTextureArray)
				{
					subTextures.emplace_back(curentSubTexture.GetString());
				}
				loatTextureAtlas(name, subTextures, filePath, subTextureWidth, subTextureHeight);
			}
		}
				auto animatedSpritesIT = document.FindMember("animatedSprites");
				if (animatedSpritesIT != document.MemberEnd())
				{
					for (const auto& curentAnimatedSprite : animatedSpritesIT->value.GetArray())
					{
						const std::string name = curentAnimatedSprite["name"].GetString();
						const std::string textureAtlas = curentAnimatedSprite["textureAtlas"].GetString();
						const std::string spriteShader = curentAnimatedSprite["shader"].GetString();
						const std::string initialSubTexture = curentAnimatedSprite["initialSubTexture"].GetString();
						auto pAnimatedSpritee = ResourceManger::loadAnimatedSprite(name, textureAtlas, spriteShader, initialSubTexture);
						if (!pAnimatedSpritee)
						{
							std::cerr << "cant Load animated sprite" << name << std::endl;
							continue;
						}
						const auto statesArray = curentAnimatedSprite["states"].GetArray();
						for (const auto& currentState : statesArray)
						{
							const std::string stateName = currentState["stateName"].GetString();
							std::vector<std::pair<std::string, uint64_t>> frames;
							const auto framesArray = currentState["frmaes"].GetArray();
							frames.reserve(framesArray.Size());
							for (const auto& currentState : framesArray)
							{
								const std::string subTexture = currentState["subTexture"].GetString();
								const uint64_t duration = currentState["duration"].GetUint64();
								frames.emplace_back(std::pair<std::string, uint64_t>(subTexture, duration));
							}
							pAnimatedSpritee->insertState(stateName, std::move(frames));
						}

					}
				}
			







				auto spritesIT = document.FindMember("sprites");
				if (spritesIT != document.MemberEnd())
				{
					for (const auto& curentSprite : spritesIT->value.GetArray())
					{
						const std::string name = curentSprite["name"].GetString();
						const std::string textureAtlas = curentSprite["textureAtlas"].GetString();
						const std::string spriteShader = curentSprite["shader"].GetString();
						const std::string subTexture = curentSprite["subTextureName"].GetString();
						auto pSpritee = ResourceManger::loadSprite(name, textureAtlas, spriteShader, subTexture);
						if (!pSpritee)
						{
							std::cerr << "cant Load sprite" << name << std::endl;
							continue;
						}
					}
				}










				auto LevelsIt = document.FindMember("levels");
				if (LevelsIt != document.MemberEnd())
				{
					for (const auto& curentLevel : LevelsIt->value.GetArray())
					{
						const auto descriptionArray = curentLevel["description"].GetArray();
						std::vector<std::string>lewelRows;
						lewelRows.reserve(descriptionArray.Size());
						size_t maxLenght = 0;
						for (const auto& curentLevel : descriptionArray)
						{
							lewelRows.emplace_back(curentLevel.GetString());
							if (maxLenght < lewelRows.back().length())
							{
								maxLenght = lewelRows.back().length();
							}
						}
						for (auto& curentLevel : lewelRows)
						{
							while (curentLevel.length() < maxLenght)
							{
								curentLevel.append("D");
							}
						}
						m_levels.emplace_back(std::move(lewelRows));
					}
				}
		
		return true;
	
}


