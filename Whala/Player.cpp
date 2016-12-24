#include "Player.h"

#include <algorithm>
#include "Level.h"

#include <SDL/SDL.h>
#include <iostream>

#include <KlaoudeEngine/RessourceManager.h>

#include <ctime>
#include <chrono>

Player::Player() : m_inputManager(nullptr), Entity(SIZE_X, SIZE_Y)
{
}

Player::~Player()
{
}

void Player::init(glm::vec2 speed,
	glm::vec2 position,
	KlaoudeEngine::InputManager* inputManager,
	KlaoudeEngine::Camera2D* camera)
{
	m_speed = speed;
	m_position = position;
	m_inputManager = inputManager;
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
	m_camera = camera;
	m_textureID = KlaoudeEngine::RessourceManager::getTexture("Textures/Player.png").id;
}


void Player::update(const std::vector<std::string>& levelData, float deltaTime)
{
	if (m_isJumping)
	{
		t = time - t0;
		m_position.y = pos0.y + speed0.y*t - t*t*0.005f;

		if (isGrounded(levelData))
			m_isJumping = false;
	}

	m_direction = glm::vec2(1, 0);
	applyForce(deltaTime, levelData);

	if (m_inputManager->isKeyDown(SDLK_s))
		m_position.y -= m_speed.x * deltaTime;

	else if (m_inputManager->isKeyDown(SDLK_z))
	{
		if (!m_isJumping && isGrounded(levelData))
		{
			t0 = time;
			pos0 = m_position;
			speed0 = m_speed;
			speed0.y += 1.5f;
			m_isJumping = true;
		}
	}
	if (m_inputManager->isKeyDown(SDLK_q))
		m_position.x -= m_speed.x * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_d))
		m_position.x += m_speed.x * deltaTime;

	if (isGrounded(levelData))
		std::cout << "Bite" << std::endl;

	collideWithLevel(levelData);	
	time++;
}

void Player::applyForce(float deltaTime, const std::vector<std::string>& levelData)
{
	gravity = -0.5f;
	m_position.y += gravity;
}

bool Player::isGrounded(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;

	checkTilePosition(levelData, collideTilePos, m_position.x, m_position.y);
	checkTilePosition(levelData, collideTilePos, m_position.x + SIZE_X, m_position.y);

	if (collideTilePos.size() == 0)
		return false;

	for each(glm::vec2 collide in collideTilePos)
		if (checkTile(collide))
			return true;
	return false;
}

bool Player::checkTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = float(TILE_WIDTH) / 2.0f;
	const float MIN_DIST_Y = SIZE_Y / 2.f + TILE_RADIUS;

	glm::vec2 centerPlayerPos = m_position + glm::vec2(SIZE_X / 2.f, SIZE_Y / 2.f);
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
