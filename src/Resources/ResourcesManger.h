#pragma once

#include <iostream>
#include <string>
#include<memory>
#include <map>
#include <vector>


namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
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
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);

	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
												 const std::string& textureName,
												 const std::string& shaderName,
												 const unsigned int spriteWidth,
												 const unsigned int spriteHeight,
		                                         const std::string& subTextureName = "default");

	std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");

	std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


	std::shared_ptr<Renderer::Texture2D> loatTextureAtlas(const std::string& textureName,
		const std::vector<std::string> subTextures,
		const std::string& texturePath,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHight);


	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
	std::string getFileString(const std::string& relatveFilePath) const;

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_shaderProgram;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
	SpriteMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpriteeMap;
	AnimatedSpriteeMap m_AnimatedSprite;

	std::string m_path;

};