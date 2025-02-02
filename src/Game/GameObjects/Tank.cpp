#include "Tank.h"
#include"Bullet.h"
#include "../../Resources/ResourcesManger.h"
#include "../../Physics/PhysicsEngine.h"

Tank::Tank(
	const double maxVelocity, const glm::vec2& position, const glm::vec2& size, const float layer):
	IGameObject(IGameObject::EObjectType::Tank,position,size,0.f,layer),
	m_eOrintation(EOrintation::top),
	m_pCurrentBullet(std::make_shared<Bullet>(0.1,m_position+m_size/4.f,m_size/2.f,m_size,layer)),
	m_pSprite_top(ResourceManger::getSprite("tankTopState")),
	m_pSprite_bottom(ResourceManger::getSprite("tankBottomState")),
	m_pSprite_left(ResourceManger::getSprite("tankLeftState")),
	m_pSprite_right(ResourceManger::getSprite("tankRightState")),
	m_pSprite_respawn(ResourceManger::getSprite("respown_animation")),
	m_pSprite_shild(ResourceManger::getSprite("shild_animation")),
	m_spriteAnimator_top(m_pSprite_top),
	m_spriteAnimator_bottom(m_pSprite_bottom),
	m_spriteAnimator_left(m_pSprite_left),
	m_spriteAnimator_right(m_pSprite_right),
	m_spriteAnimator_respawn(m_pSprite_respawn),
	m_spriteAnimator_shild(m_pSprite_shild),
	m_maxVelocity(maxVelocity),
	m_isSpawning(true),
	m_isShild(false)
{
	m_spawnTimer.setCallback([&]()
		{
			m_isSpawning = false;
			m_isShild = true;
			m_shildTimer.start(2000);

		});
	m_spawnTimer.start(2000);
	m_shildTimer.setCallback([&]()
	    {
			m_isShild = false; 
		});
	m_colliders.emplace_back(glm::vec2(0), m_size);
	Physics::PhysicsEngine::addDynamicGameObject(m_pCurrentBullet);
}


void Tank::render() const
{
	if (m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->render();
	}
	if (m_isSpawning)
	{
		m_pSprite_respawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_respawn.getCurrentFrame());
	}
	else {

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
		if (m_isShild)
		{
			m_pSprite_shild->render(m_position, m_size, m_rotation, m_layer + 0.1f, m_spriteAnimator_shild.getCurrentFrame());
		}
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
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case Tank::EOrintation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case Tank::EOrintation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case Tank::EOrintation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	default:
		break;
	}
}

void Tank::update(const double delta)
{
	if (m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->update(delta);
	}
	if (m_isSpawning)
	{
		m_spriteAnimator_respawn.update(delta);
		m_spawnTimer.update(delta);
	}
	else {

		if (m_isShild)
		{
			m_spriteAnimator_shild.update(delta);
			m_shildTimer.update(delta);
		}
		if (m_velocity > 0)
		{
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
}

double Tank::getMaxVelocity() const
{
	return m_maxVelocity;
}

void Tank::setVelocity(const double velocity)
{
	if (!m_isSpawning)
	{
		m_velocity = velocity;
	}
}

void Tank::fire()
{
	if (!m_isSpawning && !m_pCurrentBullet->isActive())
	{
		m_pCurrentBullet->fire(m_position + m_size / 4.f + m_size * m_direction/4.f,m_direction);
		
	}
}
