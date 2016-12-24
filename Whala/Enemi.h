#pragma once

#include "Entity.h"

class Enemi : public Entity
{
public:
	Enemi();
	~Enemi();

	void init(glm::vec2 speed,	glm::vec2 position);

	void update(const std::vector<std::string>& levelData, float deltaTime) override;

private:
};

