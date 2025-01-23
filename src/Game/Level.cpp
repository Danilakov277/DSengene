#include "Level.h"
#include "GameObjects/IGameObject.h"
#include "GameObjects/BrickWall.h"
#include "GameObjects/BetonWall.h"
#include "GameObjects/Trees.h"
#include "GameObjects/Ise.h"
#include "GameObjects/Woter.h"
#include "GameObjects/Eagle.h"
#include "GameObjects/Border.h"

#include <algorithm>
#include <iostream>
#include <cmath>




std::shared_ptr<IGameObject> createdGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	switch (description)
	{
	 case'J':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopRight, position, size, rotation, 0.f);
	 case'G':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomLeft, position, size, rotation, 0.f);
	 case'H':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::BottomRight, position, size, rotation, 0.f);
	 case'I':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::TopLeft, position, size, rotation, 0.f);
	case'0':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Right,position,size,rotation, 0.f);
	 case'1':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Bottom, position, size, rotation, 0.f);
	 case'2':
		return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Left, position, size, rotation, 0.f);
	 case'3':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::Top, position, size, rotation, 0.f);
	 case'4':
		 return std::make_shared<BrickWall>(BrickWall::EBrickWallType::All, position, size, rotation, 0.f);


	 case'5':
		 return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Right, position, size, rotation, 0.f);
	 case'6':
		 return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Bottom, position, size, rotation, 0.f);
	 case'7':
		 return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Left, position, size, rotation, 0.f);
	 case'8':
		 return std::make_shared<BetonWall>(BetonWall::EBetonWallType::Top, position, size, rotation, 0.f);
	 case'9':
		 return std::make_shared<BetonWall>(BetonWall::EBetonWallType::All, position, size, rotation, 0.f);


	 case'B':
		 return std::make_shared<Trees>( position, size, rotation, 1.f);


	 case'C':
		 return std::make_shared<Ise>(position, size, rotation, -1.f);

	 case'A':
		 return std::make_shared<Woter>(position, size, rotation, 0.f);

	 case'E':
		 return std::make_shared<Eagle>(position, size, rotation, 0.f);

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
	m_widthBlocks = levelDiscription[0].length();
	m_hightBlocks = levelDiscription.size();

	m_widthPixels =static_cast<unsigned int>( m_widthBlocks * BLOCK_SIZE);
	m_hightPixels = static_cast<unsigned int>(m_hightBlocks * BLOCK_SIZE);

	m_playerRespawn_1 = { BLOCK_SIZE * (m_widthBlocks / 2 - 1),BLOCK_SIZE / 2 };
	m_playerRespawn_2 = { BLOCK_SIZE * (m_widthBlocks / 2 + 3),BLOCK_SIZE / 2 };

	m_enemyRespawn_1 = { BLOCK_SIZE,m_hightBlocks +(BLOCK_SIZE) - BLOCK_SIZE/2 };
	m_enemyRespawn_1 = { BLOCK_SIZE*(m_widthBlocks /2+1),m_hightBlocks +(BLOCK_SIZE) - BLOCK_SIZE/2 };
	m_enemyRespawn_1 = { BLOCK_SIZE * m_widthBlocks,m_hightBlocks + (BLOCK_SIZE)-BLOCK_SIZE / 2};

	m_mapObjects.reserve(static_cast<size_t>(m_widthBlocks) * m_hightBlocks +4);
	unsigned int currentBottomOffset = BLOCK_SIZE * (m_hightBlocks - 1)+BLOCK_SIZE/2.f;
	for (const std::string& currentRow : levelDiscription)
	{
		unsigned int currentLeftOffset = BLOCK_SIZE;
		for (const char currentElement : currentRow)
		{

			switch (currentElement)
			{
			case 'K':
				m_playerRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_mapObjects.emplace_back(nullptr);
				break;
			case 'L':
				m_playerRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_mapObjects.emplace_back(nullptr);
				break;
			case 'M':
				m_enemyRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_mapObjects.emplace_back(nullptr);
				break;
			case 'N':
				m_enemyRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_mapObjects.emplace_back(nullptr);
				break;
			case 'O':
				m_enemyRespawn_3 = { currentLeftOffset, currentBottomOffset };
				m_mapObjects.emplace_back(nullptr);
				break;
			default:
				m_mapObjects.emplace_back(createdGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0.f));
				break;
			}


			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	//bottomborder
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE,0.f),glm::vec2(m_widthBlocks *BLOCK_SIZE,BLOCK_SIZE/2),0.f,0.f));

	//top border
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE,m_hightBlocks *BLOCK_SIZE+BLOCK_SIZE/2.f),glm::vec2(m_widthBlocks *BLOCK_SIZE,BLOCK_SIZE/2.f),0.f,0.f));
	
	//left border
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2(0.f,0.f),glm::vec2(BLOCK_SIZE,(m_hightBlocks +1)*BLOCK_SIZE),0.f,0.f));
	//right border
	m_mapObjects.emplace_back(std::make_shared<Border>(glm::vec2((m_widthBlocks +1)*BLOCK_SIZE,0.f),glm::vec2(2.0f*BLOCK_SIZE, (m_hightBlocks + 1) * BLOCK_SIZE),0.f,0.f));



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

void Level::update(const double delta)
{
	for (const auto& currentMapObject : m_mapObjects)
	{
		if (currentMapObject)
		{
			currentMapObject->update(delta);
		}
	}
}

size_t Level::getLevelWidth() const
{
	return(m_widthBlocks + 3) * BLOCK_SIZE;
}

size_t Level::getLevelHeight() const
{
	return (m_hightBlocks + 1) * BLOCK_SIZE;
}

std::vector<std::shared_ptr<IGameObject>> Level::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const
{
	std::vector<std::shared_ptr<IGameObject>> output;
	output.reserve(9);

	glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_hightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_hightPixels)));
	glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_hightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_hightPixels)));

	size_t startX = static_cast<size_t>(floor(bottomLeft_converted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRight_converted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(topRight_converted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto& currentObject = m_mapObjects[currentRow * m_widthBlocks + currentColumn];
				
			if (currentObject)
			{
				output.push_back(currentObject);
			}
		}
	}
	if (endX >= m_widthBlocks)
	{
		output.push_back(m_mapObjects[m_mapObjects.size() - 1]);
	}
	if (startX <= 1)
	{
		output.push_back(m_mapObjects[m_mapObjects.size() - 2]);
	}
	if (startY <= 1)
	{
		output.push_back(m_mapObjects[m_mapObjects.size() - 3]);
	}
	if (endY >= m_hightBlocks)
	{
		output.push_back(m_mapObjects[m_mapObjects.size() - 4]);
	}
	
	return output;
}
