#include "Level.h"
#include "../Resources/ResourcesManger.h"
#include "GameObjects/IGameObject.h"
#include "GameObjects/BrickWall.h"

#include <iostream>

const unsigned int BLOCK_SIZE = 16;

std::shared_ptr<IGameObject> createdGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (description)
	{
	 case'J':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("topRightbrickWall"), position, size, rotation);
	 case'G':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("bottomLeftbrickWall"), position, size, rotation);
	 case'H':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("bottomRightbrickWall"), position, size, rotation);
	 case'I':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("topLeftbrickWall"), position, size, rotation);
	case'0':
		return std::make_shared<BrickWall>(ResourceManger::getSprite("rightbrickWall"),position,size,rotation);
	 case'1':
		return std::make_shared<BrickWall>(ResourceManger::getSprite("bottombrickWall"), position, size, rotation);
	 case'2':
		return std::make_shared<BrickWall>(ResourceManger::getSprite("leftbrickWall"), position, size, rotation);
	 case'3':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("topbrickWall"), position, size, rotation);
	 case'4':
		 return std::make_shared<BrickWall>(ResourceManger::getSprite("brickWall"), position, size, rotation);
	 case'D':
		 return nullptr;
	default:
		std::cerr << "unknown GameObject decription" <<description<< std::endl;
		break;
	}
	return nullptr;
}


Level::Level(const std::vector<std::string>& levelDiscription)
{
	if (levelDiscription.empty())
	{
		std::cerr << "Empty level Discription" << std::endl;
	}
	m_width = levelDiscription[0].length();
	m_hight = levelDiscription.size();

	m_mapObjects.reserve(static_cast<size_t>(m_width) * m_hight);
	unsigned int currentBottomOffset = BLOCK_SIZE * (m_hight - 1);
	for (const std::string& currentRow : levelDiscription)
	{
		unsigned int currentLeftOffset = 0;
		for (const char currentElement : currentRow)
		{

		m_mapObjects.emplace_back(	createdGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE),0.f));

			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

}

void Level::render() const
{
	for (const auto& currentMapObject : m_mapObjects)
	{
		if (currentMapObject)
		{
			currentMapObject->render();
		}
	}
}

void Level::update(const uint64_t delta)
{
	for (const auto& currentMapObject : m_mapObjects)
	{
		if (currentMapObject)
		{
			currentMapObject->update(delta);
		}
	}
}
