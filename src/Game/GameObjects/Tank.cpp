#include "Tank.h"

#include "../../Resources/ResourcesManger.h"

Tank::Tank(
	const double velocity, const glm::vec2& position, const glm::vec2& size, const float layer):
	IGameObject(position,size,0.f,layer),
	m_eOrintation(EOrintation::top),
	m_pSprite_top(ResourceManger::getSprite("tankTopState")),
	m_pSprite_bottom(ResourceManger::getSprite("tankBottomState")),
	m_pSprite_left(ResourceManger::getSprite("tankLeftState")),
	m_pSprite_right(ResourceManger::getSprite("tankRightState")),
	m_spriteAnimator_top(m_pSprite_top),
	m_spriteAnimator_bottom(m_pSprite_bottom),
	m_spriteAnimator_left(m_pSprite_left),
	m_spriteAnimator_right(m_pSprite_right),
	m_move(false),
	m_velocity(velocity),
	m_moveOffset(glm::vec2(0.f,1.f))
{

}

void Tank::render() const
{
	switch (m_eOrintation)
	{
	case Tank::EOrintation::top:
		m_pSprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top.getCurrentFrame());
		break;
	case Tank::EOrintation::Bottom:
		m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom.getCurrentFrame());
		break;
	case Tank::EOrintation::Left:
		m_pSprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left.getCurrentFrame());
		break;
	case Tank::EOrintation::Right:
		m_pSprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right.getCurrentFrame());
		break;
	}

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
		m_moveOffset.x = 0.f;
		m_moveOffset.y = 1.f;
		break;
	case Tank::EOrintation::Bottom:
		m_moveOffset.x = 0.f;
		m_moveOffset.y = -1.f;
		break;
	case Tank::EOrintation::Left:
		m_moveOffset.x = -1.f;
		m_moveOffset.y = 0.f;
		break;
	case Tank::EOrintation::Right:
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

void Tank::update(const double delta)
{
	if (m_move)
	{
		m_position.y += static_cast<float>( delta * m_velocity * m_moveOffset.y);
		m_position.x += static_cast<float>( delta * m_velocity * m_moveOffset.x);
		

		switch (m_eOrintation)
		{
		case Tank::EOrintation::top:
			m_spriteAnimator_top.update(delta);
			break;
		case Tank::EOrintation::Bottom:
			m_spriteAnimator_bottom.update(delta);
			break;
		case Tank::EOrintation::Left:
			m_spriteAnimator_left.update(delta);
			break;
		case Tank::EOrintation::Right:
			m_spriteAnimator_right.update(delta);
			break;
		}

	}
}
