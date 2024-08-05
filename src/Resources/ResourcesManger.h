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
	

	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();

	~ResourceManger() = delete;
	ResourceManger() = delete;
	ResourceManger(const ResourceManger&) = delete;
	ResourceManger& operator = (const ResourceManger&) = delete;
	ResourceManger& operator = (ResourceManger&&) = delete;
	ResourceManger(ResourceManger&&) = delete;

	static std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	static std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);

	static std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
												 const std::string& textureName,
												 const std::string& shaderName,
												 const unsigned int spriteWidth,
												 const unsigned int spriteHeight,
		                                         const std::string& subTextureName = "default");

	static std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");

	static std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


	static std::shared_ptr<Renderer::Texture2D> loatTextureAtlas(const std::string& textureName,
		const std::vector<std::string> subTextures,
		const std::string& texturePath,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHight);


	static std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
	static std::string getFileString(const std::string& relatveFilePath);

	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	static ShaderProgramMap m_shaderProgram;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpriteMap;
	static SpriteMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpriteeMap;
	static AnimatedSpriteeMap m_AnimatedSprite;

	static std::string m_path;

};