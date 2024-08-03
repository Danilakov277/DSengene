#pragma once

#include "Sprite.h"
#include <map>
#include <vector>

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;

	class AnimatedSprite : public Sprite
	{
	public:
		AnimatedSprite(const std::shared_ptr<Texture2D> pTexure,
			const std::string initialSubTexture,
			const std::shared_ptr<ShaderProgram> pShaderProgram,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f),
		    const float rotation = 0.f);
	private:
		std::map < std::string, std::vector<std::pair<std::string, size_t>>> m_statesMap;

	};

}