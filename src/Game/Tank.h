#pragma once
#include "../Render/AnimatedSprite.h"
#include <glm/vec2.hpp>
#include <memory>

namespace RenderEngine
{
	class AnimatedSprite;
}
class Tank
{
public:

	enum class EOrintation
	{
		top,
		Bottom,
		Left,
		Right
	};

	Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite,const float velocity, const glm::vec2& position);
	void render() const;
	void setOrintation(const EOrintation eOrintation);
	void move(const bool move);
	void update(const uint64_t delta);

private:
	EOrintation m_eOrintation;
	std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;
	bool m_move;
	float m_velocity;
	glm::vec2 m_position;
	glm::vec2 m_moveOffset;
};