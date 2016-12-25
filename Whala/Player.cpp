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

void Player::update(const std::vector<std::string>& levelData, float deltaTime, Player* player)
{
	if (m_inputManager->isKeyDown(SDLK_LEFT))
	{
		m_speed.x = -4 * deltaTime;
	}
	else if (m_inputManager->isKeyDown(SDLK_RIGHT))
	{
		m_speed.x = 4 * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_DOWN))
		m_position.y -= m_speed.x * deltaTime;

	else if (m_inputManager->isKeyDown(SDLK_UP))
		m_isJumping = true;

	jump(deltaTime, levelData, m_inputManager);

	applyForce(deltaTime, levelData);

	collideWithLevel(levelData);

	if (m_imunity > 0)
		m_imunity--;

	std::cout << m_speed.y << std::endl;
}

void Player::takeDamage(float damage)
{
	if (m_imunity == 0)
	{
		m_health -= damage;
		m_imunity = 1000;
	}		
}