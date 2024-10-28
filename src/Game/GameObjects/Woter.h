#pragma once


#include "IGameObject.h"
#include "../../Render/SpriteAnimator.h"
#include <array>
#include <memory>

namespace RenderEngine
{
  class	Sprite;
}

class Woter : public IGameObject
{
public:


	enum class EBlockLocation
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	Woter( const glm::vec2& position, const glm::vec2& size, const float rotation,const float layer);
	virtual void render() const override;
	void update(const uint64_t delta) override;

private:
	void renderBlock(const EBlockLocation eBlockLocation) const;

	std::shared_ptr<RenderEngine::Sprite> m_sprites;
	RenderEngine::SpriteAnimator m_spriteAnimator;
	std::array<glm::vec2, 4> m_blockOffsets;

};