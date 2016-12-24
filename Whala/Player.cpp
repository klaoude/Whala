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
	m_jumpForce = 0.06 * deltaTime;
	if (m_isJumping)
	{
		if (m_dJumpForce > 0)
			m_dJumpForce -= 0.001 * deltaTime;
		else
			m_dJumpForce = 0;
	}
	else
		m_dJumpForce = m_jumpForce;

	m_direction = glm::vec2(1, 0);
	applyForce(deltaTime, levelData);

	if (m_inputManager->isKeyDown(SDLK_s))
		m_position.y -= m_speed.x * deltaTime;

	else if (m_inputManager->isKeyDown(SDLK_z))
		m_isJumping = true;

	if (m_inputManager->isKeyDown(SDLK_q))
		m_speed.x = -4 * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_d))
		m_speed.x = 4 * deltaTime;


	applyForce(deltaTime, levelData);
	if (isGrounded(levelData) && m_isJumping)
		m_isJumping = false;

	std::cout << m_speed.y << std::endl;


	collideWithLevel(levelData);	
	time++;
}



void Player::applyForce(float deltaTime, const std::vector<std::string>& levelData)
{
	gravity = -0.01f * deltaTime;
	if (isGrounded(levelData))
		m_speed.y -= 2*gravity;
	m_speed.y += gravity;
	if (m_isJumping)
		m_speed.y += m_dJumpForce;
	m_position += m_speed;
	m_speed.x = 0;
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
