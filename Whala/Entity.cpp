#include "Entity.h"
#include "Level.h"
#include <algorithm>

Entity::Entity(int sizeX, int sizeY) : m_speed(0.f), m_sizeX(sizeX), m_sizeY(sizeY)
{
}

Entity::~Entity()
{
}

bool Entity::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	checkTilePosition(levelData, collideTilePos, m_position.x, m_position.y);
	checkTilePosition(levelData, collideTilePos, m_position.x + m_sizeX, m_position.y);
	checkTilePosition(levelData, collideTilePos, m_position.x, m_position.y + m_sizeY);
	checkTilePosition(levelData, collideTilePos, m_position.x + m_sizeX, m_position.y + m_sizeY);

	if (collideTilePos.size() == 0)
		return false;

	for each(glm::vec2 collide in collideTilePos)
		collideWithTile(collide);

	return true;
}

void Entity::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, m_sizeX, m_sizeY);

	spritebatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}

void Entity::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / float(TILE_WIDTH)),
		floor(y / float(TILE_WIDTH)));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 1 || cornerPos.y >= levelData.size())
		return;

	if (levelData[cornerPos.y-1][cornerPos.x] != '.')
		collideTilePos.push_back(cornerPos * float(TILE_WIDTH) + glm::vec2(TILE_WIDTH / 2.0f));
}

void Entity::collideWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = float(TILE_WIDTH) / 2.0f;
	const float MIN_DIST_X = m_sizeX / 2.f + TILE_RADIUS;
	const float MIN_DIST_Y = m_sizeY / 2.f + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xdepth = MIN_DIST_X - abs(distVec.x);
	float ydepth = MIN_DIST_Y - abs(distVec.y);

	if (xdepth > 0 || ydepth > 0)
	{
		if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f))
		{
			if (distVec.x < 0)
				m_position.x -= xdepth;
			else
				m_position.x += xdepth;
		}
		else
		{
			if (distVec.y < 0)
				m_position.y -= ydepth;
			else
				m_position.y += ydepth;
		}
	}
}

bool Entity::isGrounded(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	checkTilePosition(levelData, collideTilePos, m_position.x + m_sizeX / 2.f, m_position.y);

	if (collideTilePos.size() == 0)
		return false;

	for each(glm::vec2 collide in collideTilePos)
		if (checkTileGround(collide))
			return true;
	return false;
}

bool Entity::checkTileGround(glm::vec2 tilePos)
{
	const float TILE_RADIUS = float(TILE_WIDTH) / 2.0f;
	const float MIN_DIST_Y = m_sizeY / 2.f + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float ydepth = MIN_DIST_Y - abs(distVec.y);

	if (ydepth > 0)
	{
		if (distVec.y < 0)
			return false;
		else
			return true;
	}
}

bool Entity::checkTileTop(glm::vec2 tilePos)
{
	const float TILE_RADIUS = float(TILE_WIDTH) / 2.0f;
	const float MIN_DIST_Y = m_sizeY / 2.f + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 distVec = centerPlayerPos - tilePos;

	float ydepth = MIN_DIST_Y - abs(distVec.y);

	if (ydepth > 0)
	{
		if (distVec.y < 0)
			return true;
		else
			return false;
	}
}

bool Entity::isPlafon(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	checkTilePosition(levelData, collideTilePos, m_position.x + m_sizeX / 2.f, m_position.y + m_sizeY);

	if (collideTilePos.size() == 0)
		return false;

	for each(glm::vec2 collide in collideTilePos)
		if (checkTileTop(collide))
			return true;
	return false;
}