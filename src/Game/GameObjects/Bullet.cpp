#include "Bullet.h"
#include "../../Resources/ResourcesManger.h"
#include"../../Render/Sprite.h"

Bullet::Bullet(const double velosity, const glm::vec2& position, const glm::vec2& size, const glm::vec2& explisionSize, const float layer):
IGameObject(IGameObject::EObjectType::Bullet,position,size,0.f,layer),
m_explosionSize(explisionSize),
m_explosionOffset((m_explosionSize-m_size)/2.f),
m_pSprite_top(ResourceManger::getSprite("bullet_Top")),
m_pSprite_bottom(ResourceManger::getSprite("bullet_Bottom")),
m_pSprite_left(ResourceManger::getSprite("bullet_Left")),
m_pSprite_right(ResourceManger::getSprite("bullet_Right")),
m_pSprite_explosion(ResourceManger::getSprite("explosion")),
m_spriteAnimator_explosion(m_pSprite_explosion),
m_eOrintation(EOrintation::Top),
m_maxVelocity(velosity),
m_isActive(false),
m_isExplosion(false)
{
	m_colliders.emplace_back(glm::vec2(0), m_size);

	m_explosionTimer.setCallback([&]()
		{
			std::cout << "1111" << std::endl;
			m_isExplosion = false;
			m_isActive = false;
		}
	);
}

void Bullet::render() const
{
	if (m_isActive) {

		if (m_isExplosion)
		{
			switch (m_eOrintation)
			{
			case Bullet::EOrintation::Top:
				m_pSprite_explosion->render(m_position - m_explosionOffset + glm::vec2(0, m_size.y / 2.f), m_explosionSize, m_rotation, m_layer, m_spriteAnimator_explosion.getCurrentFrame());
				break;
			case Bullet::EOrintation::Bottom:
				m_pSprite_explosion->render(m_position - m_explosionOffset - glm::vec2(0, m_size.y / 2.f), m_explosionSize, m_rotation, m_layer, m_spriteAnimator_explosion.getCurrentFrame());
				break;
			case Bullet::EOrintation::Left:
				m_pSprite_explosion->render(m_position - m_explosionOffset - glm::vec2(m_size.x / 2.f, 0), m_explosionSize, m_rotation, m_layer, m_spriteAnimator_explosion.getCurrentFrame());
				break;
			case Bullet::EOrintation::Right:
				m_pSprite_explosion->render(m_position - m_explosionOffset + glm::vec2(m_size.x / 2.f, 0), m_explosionSize, m_rotation, m_layer,m_spriteAnimator_explosion.getCurrentFrame());
				break;
			default:
				break;
			}
		}
		else {
			switch (m_eOrintation)
			{
			case Bullet::EOrintation::Top:
				m_pSprite_top->render(m_position, m_size, m_rotation, m_layer);
				break;
			case Bullet::EOrintation::Bottom:
				m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer);
				break;
			case Bullet::EOrintation::Left:
				m_pSprite_left->render(m_position, m_size, m_rotation, m_layer);
				break;
			case Bullet::EOrintation::Right:
				m_pSprite_right->render(m_position, m_size, m_rotation, m_layer);
				break;
			}
		}
	}
}

void Bullet::update(const double delta)
{
	if (m_isExplosion)
	{
		std::cout << "updatind" << std::endl;
		m_spriteAnimator_explosion.update(delta);
		m_explosionTimer.update(delta);
	}
}

void Bullet::fire(const glm::vec2& position, const glm::vec2& direction)
{
	m_position = position;
	m_direction = direction;
	if (m_direction.x == 0.f)
	{
		m_eOrintation = (m_direction.y < 0) ? EOrintation::Bottom : EOrintation::Top;
	}
	else
	{
		m_eOrintation = (m_direction.x < 0) ? EOrintation::Left : EOrintation::Right;
	}
	m_isActive = true;
	setVelocity(m_maxVelocity);
}
void Bullet::onCollision()
{
	setVelocity(0);
	m_isExplosion = true;
	m_spriteAnimator_explosion.reset();
	m_explosionTimer.start(m_spriteAnimator_explosion.getTotalDuration());
	std::cout << m_spriteAnimator_explosion.getTotalDuration() << std::endl;
}
