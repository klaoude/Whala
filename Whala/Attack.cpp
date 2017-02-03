#include "Attack.h"

#include <KlaoudeEngine\RessourceManager.h>

#include "Entity.h"
#include "Level.h"

Attack::Attack(glm::vec2 position, glm::vec2 direction, float speed, float damage, float sizeX, float sizeY, bool left, int lifeTime)
{
	m_position = position;
	m_direction = direction;
	m_speed = speed;
	m_damage = damage;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_lifeTime = lifeTime;
	m_left = left;
	m_frameCounter = 0.f;
}

Attack::~Attack() {}

bool Attack::update(const std::vector<std::string>& levelData, float deltaTime)
{
	m_frameCounter += 1.0f * deltaTime;

	if (m_frameCounter >= m_lifeTime)
		return true;

	if(m_left)
		m_position -= m_direction * m_speed * deltaTime;
	else
		m_position += m_direction * m_speed * deltaTime;

	return false;//return CollideWithWorld(levelData);
}

void Attack::draw(KlaoudeEngine::SpriteBatch & spriteBatch)
{
	glm::vec4 destRect(m_position.x + m_sizeX, m_position.y + m_sizeY, m_sizeX * 2.f, m_sizeY * 2.f);
	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);

	if (m_left)
	{
		uvRect.x += 1.f / m_sizeX;
		uvRect.z *= -1;
	}		

	KlaoudeEngine::ColorRGBA8 color(255, 255, 255, 255);

	spriteBatch.draw(destRect, uvRect, KlaoudeEngine::RessourceManager::getTexture("Textures/Attack.png").id, 0.f, color);
}

bool Attack::collideWithEntity(Entity* entity)
{
	const float MIN_DIST_X = entity->getSizeX() / 2.f + m_sizeX / 2.f;
	const float MIN_DIST_Y = entity->getSizeY() / 2.f + m_sizeY / 2.f;

	glm::vec2 centerPosA = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(entity->getSizeX() / 2.f, entity->getSizeY() / 2.f);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepthX = MIN_DIST_X - distance;
	float collisionDepthY = MIN_DIST_Y - distance;	

	return collisionDepthX > 0 || collisionDepthY > 0;
}

bool Attack::CollideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(m_position.x / float(TILE_WIDTH));
	gridPosition.y = floor(m_position.y / float(TILE_WIDTH));

	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].length() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
		return true;

	return levelData[gridPosition.y][gridPosition.x] != '.';
}