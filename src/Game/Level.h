#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <glm/vec2.hpp>

class IGameObject;
class Level
{
public:
	static constexpr unsigned int BLOCK_SIZE = 16;
	Level(const std::vector<std::string>& levelDiscription);
	void render() const;
	void update(const double delta);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	const glm::ivec2& getPlayerRespawn_1() const { return m_playerRespawn_1; }
	const glm::ivec2& getPlayerRespawn_2() const { return m_playerRespawn_2; }
	const glm::ivec2& getEnemyRespawn_1() const { return m_enemyRespawn_1; }
	const glm::ivec2& getEnemyRespawn_2() const { return m_enemyRespawn_2; }
	const glm::ivec2& getEnemyRespawn_3() const { return m_enemyRespawn_3; }

	std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;

private:
	size_t m_widthBlocks;
	size_t m_hightBlocks;
	unsigned int m_widthPixels = 0;
	unsigned int m_hightPixels = 0;

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;

	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};

