#include "Woter.h"
#include"../../Resources/ResourcesManger.h"
#include "../../Render/Sprite.h"


Woter::Woter(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer) :
	IGameObject(IGameObject::EObjectType::Water,position,size,rotation,layer),
	m_sprites(ResourceManger::getSprite("woter_sprite")),
	m_spriteAnimator(m_sprites),
	m_blockOffsets{ glm::vec2(0,m_size.y / 2.f),
										  glm::vec2(m_size.x / 2.f,m_size.y / 2.f),
										  glm::vec2(0,0),
										  glm::vec2(m_size.x / 2.f,0) }
{
	
	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Woter::renderBlock(const EBlockLocation eBlockLocation) const
{


		m_sprites->render(m_position+m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size/2.f, m_rotation,m_layer,m_spriteAnimator.getCurrentFrame());
	
}


void Woter::render() const
{
	renderBlock(EBlockLocation::BottomLeft);
	renderBlock(EBlockLocation::BottomRight);
	renderBlock(EBlockLocation::TopLeft);
	renderBlock(EBlockLocation::TopRight);
}

void Woter::update(const double delta)
{
	m_spriteAnimator.update(delta);
}
bool Woter::collides(const EObjectType objectType)
{
	return objectType != IGameObject::EObjectType::Bullet;
}

