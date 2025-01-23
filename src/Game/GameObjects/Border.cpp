#include "Border.h"
#include"../../Resources/ResourcesManger.h"
#include "../../Render/Sprite.h"


Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer) :
	IGameObject(position,size,rotation,layer),
	m_sprites(ResourceManger::getSprite("border_block"))
{
	
	m_colliders.emplace_back(glm::vec2(0), m_size);
}



void Border::render() const
{
	m_sprites->render(m_position, m_size, m_rotation, m_layer);
}

