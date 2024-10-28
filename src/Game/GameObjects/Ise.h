#pragma once


#include "IGameObject.h"
#include <array>
#include <memory>

namespace RenderEngine
{
  class	Sprite;
}

class Ise : public IGameObject
{
public:


	enum class EBlockLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Ise( const glm::vec2& position, const glm::vec2& size, const float rotation);
	virtual void render() const override;


private:
	void renderBlock(const EBlockLocation eBlockLocation) const;

	std::shared_ptr<RenderEngine::Sprite> m_sprites;

	std::array<glm::vec2, 4> m_blockOffsets;

};