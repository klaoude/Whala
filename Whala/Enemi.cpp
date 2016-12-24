#include "Enemi.h"
#include <KlaoudeEngine\RessourceManager.h>

Enemi::Enemi() : Entity(16, 20){}

Enemi::~Enemi(){}

void Enemi::init(glm::vec2 speed, glm::vec2 position)
{
	m_speed = speed;
	m_position = position;

	m_color = KlaoudeEngine::ColorRGBA8(255, 0, 0, 255);
	m_textureID = KlaoudeEngine::RessourceManager::getTexture("Textures/Player.png").id;
}

void Enemi::update(const std::vector<std::string>& levelData, float deltaTime)
{
	applyForce(deltaTime, levelData);

	collideWithLevel(levelData);
}