#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Render/SpriteAnimator.h"

#include "../../System/Timer.h"

namespace RenderEngine
{
	class Sprite;
}
class Bullet;
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
		const double maxVelocity, const glm::vec2& position,const glm::vec2& size, const float layer);
	void render() const override;
	void setOrintation(const EOrintation eOrintation);
	void update(const double delta) override;
	double getMaxVelocity() const;
	void setVelocity(const double velocity) override;
	void fire();

private:
	EOrintation m_eOrintation;
	std::shared_ptr<Bullet> m_pCurrentBullet;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
	RenderEngine::SpriteAnimator m_spriteAnimator_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_right;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
	RenderEngine::SpriteAnimator m_spriteAnimator_respawn;

	std::shared_ptr<RenderEngine::Sprite> m_pSprite_shild;
	RenderEngine::SpriteAnimator m_spriteAnimator_shild;

	Timer m_spawnTimer;
	Timer m_shildTimer;

	double m_maxVelocity;
	bool m_isSpawning;
	bool m_isShild;
};