#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Render/SpriteAnimator.h"

namespace RenderEngine
{
	class Sprite;
}
class Tank:public IGameObject
{
public:

	enum class EOrintation
	{
		top,
		Bottom,
		Left,
		Right
	};

	Tank(
		const double velocity, const glm::vec2& position,const glm::vec2& size, const float layer);
	void render() const override;
	void setOrintation(const EOrintation eOrintation);
	void move(const bool move);
	void update(const double delta) override;

private:
	EOrintation m_eOrintation;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
	RenderEngine::SpriteAnimator m_spriteAnimator_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_right;
	bool m_move;
	double m_velocity;
	glm::vec2 m_moveOffset;
};