#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class IGameObject;
class Level
{
public:
	Level(const std::vector<std::string>& levelDiscription);
	void render() const;
	void update(const uint64_t delta);

private:
	unsigned int m_width;
	unsigned int m_hight;
	std::vector<std::shared_ptr<IGameObject>> m_mapObjects;
};

