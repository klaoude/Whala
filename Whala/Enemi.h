#pragma once

#include "Entity.h"

#include <random>
#include <ctime>

class Enemi : public Entity
{
public:
	Enemi();
	~Enemi();

	void init(glm::vec2 speed,	glm::vec2 position);

	void update(const std::vector<std::string>& levelData, float deltaTime, Player* player) override;

private:
	char getLeftCase(const std::vector<std::string>& levelData);
	char getRightCase(const std::vector<std::string>& levelData);

	int m_frame = 0;
	int m_dir = 1;

	std::mt19937 m_randomEngine;
};

