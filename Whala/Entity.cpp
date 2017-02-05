#include "Entity.h"
#include "Level.h"
#include <algorithm>
#include <SDL/SDL.h>

Entity::Entity(int sizeX, int sizeY, float health, float imunity) : m_speed(0.f), m_sizeX(sizeX), m_sizeY(sizeY)
{
	m_health = health;
	m_imunity = imunity;
}

Entity::~Entity()
{
}

void Entity::update(const std::vector<std::string>& levelData, float deltaTime, Player * player)
{
	m_onGround = false;
	if (isGrounded(levelData))
		m_onGround = true;
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

bool Entity::collideWithEntity(Entity* entity)
{
	const float MIN_DIST_X = m_sizeX / 2.f;
	const float MIN_DIST_Y = m_sizeY / 2.f;

	glm::vec2 centerPosA = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 centerPosB = entity->getPosition() + glm::vec2(MIN_DIST_X, MIN_DIST_Y);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepthX = MIN_DIST_X - distance;
	float collisionDepthY = MIN_DIST_Y - distance;

	if (collisionDepthX > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepthX;

		m_position += collisionDepthVec / 2.0f;
		entity->m_position -= collisionDepthVec / 2.0f;
		return true;
	}
	else if (collisionDepthY > 0)
	{
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepthY;

		m_position += collisionDepthVec / 2.0f;
		entity->m_position -= collisionDepthVec / 2.0f;
		return true;
	}

	return false;
}

void Entity::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, m_sizeX, m_sizeY);

	spritebatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color, m_direction);
}

void Entity::checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / float(TILE_WIDTH)),
		floor(y / float(TILE_WIDTH)));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
		return;

	if (levelData[cornerPos.y][cornerPos.x] != '.')
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

	checkTilePosition(levelData, collideTilePos, m_position.x + m_sizeX / 2.f, m_position.y - 0.1f);

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

void Entity::applyForce(float deltaTime)
{
	m_gravity = -0.03f;	
	m_vel.y += m_gravity;
	m_position.y += m_vel.y;
	if (m_onGround)
		m_vel.y = 0.f;
	m_position += m_speed;
}

void Entity::jump(float deltaTime, const std::vector<std::string>& levelData, KlaoudeEngine::InputManager* inputManager)
{
	if (inputManager != nullptr && inputManager->isKeyPressed(SDLK_UP) && m_onGround)
		m_vel.y = 500.f;
	/*if (inputManager != nullptr && !inputManager->isKeyDown(SDLK_UP))
	{
		if (m_vel.y < 6.f)
			m_vel.y = 6.f;
	}*/

	if (isPlafon(levelData))
	{
		m_vel.y = 0;
	}
}

//void Entity::applyForce(float deltaTime, const std::vector<std::string>& levelData)
//{
//	m_gravity = -0.03f * deltaTime;
//	if (m_onGround)
//		m_speed.y -= m_gravity;
//	m_speed.y += m_gravity;
//	if (m_isJumping)
//		m_speed.y += m_dJumpForce;
//	m_position += m_speed;
//}
//
//void Entity::jump(float deltaTime, const std::vector<std::string>& levelData, KlaoudeEngine::InputManager* inputManager)
//{
//	m_jumpForce = 0.5f * deltaTime;
//	if (m_isJumping)
//	{
//		m_jumpTime++;
//
//		if (inputManager != nullptr && m_jumpTime < 100 && inputManager->isKeyDown(SDLK_UP))
//			m_speed.y += 0.1f * deltaTime;
//
//		if (m_dJumpForce > 0)
//			m_dJumpForce -= 0.1f * deltaTime;
//		else
//			m_dJumpForce = 0;
//	}
//	else
//	{
//		m_dJumpForce = m_jumpForce;
//		m_jumpTime = 0;
//	}
//	if (m_onGround && m_dJumpForce == 0)
//	{
//		m_isJumping = false;
//		m_speed.y = 0;
//		m_dJumpForce = 0;
//	}
//	else if (m_onGround && !m_isJumping)
//		m_speed.y = 0;
//
//	if (isPlafon(levelData))
//	{
//		m_speed.y = 0;
//	}
//}

bool Entity::takeDamage(float damage)
{
	if (m_imunity == 0)
	{
		m_health -= damage;
		m_imunity = 1000;
	}
	if (m_imunity == -1)
		m_health -= damage;

	return m_health <= 0;
}