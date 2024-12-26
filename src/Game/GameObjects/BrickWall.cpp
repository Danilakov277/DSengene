#include "BrickWall.h"
#include"../../Resources/ResourcesManger.h"
#include "../../Render/Sprite.h"


BrickWall::BrickWall(const EBrickWallType eBrickWallType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer) :
	IGameObject(position,size,rotation,layer),
	m_eCurrentBrickState{ EBrickState::Destroyed, EBrickState::Destroyed, EBrickState::Destroyed, EBrickState::Destroyed},
	m_blockOffsets{ glm::vec2(0,m_size.y / 2.f),
										  glm::vec2(m_size.x / 2.f,m_size.y / 2.f),
										  glm::vec2(0,0),
										  glm::vec2(m_size.x / 2.f,0) }
{
	m_sprites[static_cast<size_t>(EBrickState::All)] = ResourceManger::getSprite("brickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft)] = ResourceManger::getSprite("topLeftbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopRight)] = ResourceManger::getSprite("topRightbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Top)] = ResourceManger::getSprite("topbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::BottomLeft)] = ResourceManger::getSprite("bottomLeftbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Left)] = ResourceManger::getSprite("rightbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_BottomLeft)] = ResourceManger::getSprite("bottomLeftTopRightbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomLeft)] = ResourceManger::getSprite("bottomRightZerobrickWall");
	m_sprites[static_cast<size_t>(EBrickState::BottomRight)] = ResourceManger::getSprite("bottomRightbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_BottomRight)] = ResourceManger::getSprite("topLeftBottomRightbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Right)] = ResourceManger::getSprite("leftbrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Top_BottomRight)] = ResourceManger::getSprite("bottomLeftZerrobrickWall");
	m_sprites[static_cast<size_t>(EBrickState::Bottom)] = ResourceManger::getSprite("bottombrickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopLeft_Bottom)] = ResourceManger::getSprite("topRightZerrobrickWall");
	m_sprites[static_cast<size_t>(EBrickState::TopRight_Bottom)] = ResourceManger::getSprite("topLeftZerrobrickWall");
	//m_sprites[static_cast<size_t>(EBrickState::Destroyed)] = ResourceManger::getSprite("brickWall");

	switch (eBrickWallType)
	{
	case EBrickWallType::All:
		m_eCurrentBrickState.fill(EBrickState::All);
		break;
	case EBrickWallType::Top:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case EBrickWallType::Bottom:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	case EBrickWallType::Left:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		break;
	case EBrickWallType::Right:		
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case EBrickWallType::TopLeft:	
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopLeft)] = EBrickState::All;
		break;
	case EBrickWallType::TopRight:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::TopRight)] = EBrickState::All;
		break;
	case EBrickWallType::BottomLeft:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomLeft)] = EBrickState::All;
		break;
	case EBrickWallType::BottomRight:
		m_eCurrentBrickState[static_cast<size_t>(EBrickLocation::BottomRight)] = EBrickState::All;
		break;
	}

}

void BrickWall::renderBrick(const EBrickLocation eBrickLocation) const
{

	const EBrickState state = m_eCurrentBrickState[static_cast<size_t>(eBrickLocation)];
	if (state != EBrickState::Destroyed)
	{
		m_sprites[static_cast<size_t>(state)]->render(m_position+m_blockOffsets[static_cast<size_t>(eBrickLocation)], m_size/2.f, m_rotation,m_layer);
	}
}


void BrickWall::render() const
{
	renderBrick(EBrickLocation::BottomLeft);
	renderBrick(EBrickLocation::BottomRight);
	renderBrick(EBrickLocation::TopLeft);
	renderBrick(EBrickLocation::TopRight);
}

void BrickWall::update(const double delta)
{
}
