#include "Tank.h"

Tank::Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position):
	m_eOrintation(EOrintation::top),
	m_pSprite(std::move(pSprite)),
	m_move(false),
	m_velocity(velocity),
	m_position(position),
	m_moveOffset(glm::vec2(0.f,1.f))
{
	m_pSprite->setPosition(m_position);
}

void Tank::render() const
{
	m_pSprite->render();
}

void Tank::setOrintation(const EOrintation eOrintation)
{
	if (m_eOrintation == eOrintation)
	{
		return;
	}
	m_eOrintation = eOrintation;
	switch (m_eOrintation)
	{
	case Tank::EOrintation::top:
		m_pSprite->setState("tankTopState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Tank::EOrintation::Bottom:
		m_pSprite->setState("tankBottomState");
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Tank::EOrintation::Left:
		m_pSprite->setState("tankLeftState");
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Tank::EOrintation::Right:
		m_pSprite->setState("tankRightState");
		m_moveOffset.x = 1.f;
		m_moveOffset.y = 0.f;
		break;
	default:
		break;
	}
}

void Tank::move(const bool move)
{
	m_move = move;
}

void Tank::update(const uint64_t delta)
{
	if (m_move)
	{
		m_position += delta * m_velocity * m_moveOffset;
		m_pSprite->setPosition(m_position);
		m_pSprite->update(delta);
	}
}
