#include "Player.h"

#include <algorithm>
#include "Level.h"

#include <SDL/SDL.h>
#include <iostream>

#include <KlaoudeEngine/RessourceManager.h>

#include <ctime>
#include <chrono>

Player::Player() : m_inputManager(nullptr), Entity(SIZE_X, SIZE_Y, 100, 0)
{
}

Player::~Player()
{
}

void Player::init(glm::vec2 speed,
	glm::vec2 position,
	std::vector<Attack>* attacks,
	KlaoudeEngine::InputManager* inputManager,
	KlaoudeEngine::Camera2D* camera)
{	
	m_speed = speed;
	m_position = position;
	m_inputManager = inputManager;
	m_attacks = attacks;
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
		m_left = true;
	}
	else if (m_inputManager->isKeyDown(SDLK_RIGHT))
	{
		m_speed.x = 4 * deltaTime;
		m_left = false;
	}
	if (m_inputManager->isKeyDown(SDLK_DOWN))
		m_position.y -= m_speed.x * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_UP))
		m_isJumping = true;

	if (m_zCooldown == 0 && m_inputManager->isKeyDown(SDLK_z))
	{
		if (m_left)
			m_attacks->push_back(Attack(glm::vec2(m_position.x - m_sizeX - 8.f, m_position.y + m_sizeY / 2.f - 8.f * 2.f),
				glm::vec2(1.f, 0.f), 0.f, 10.f, 8.f, 8.f, 100));
		else
			m_attacks->push_back(Attack(glm::vec2(m_position.x + m_sizeX, m_position.y + m_sizeY / 2.f - 8.f * 2.f),
				glm::vec2(1.f, 0.f), 0.f, 10.f, 8.f, 8.f, 100));

		m_zCooldown = 150;
	}
		

	jump(deltaTime, levelData, m_inputManager);

	applyForce(deltaTime, levelData);

	collideWithLevel(levelData);

	if (m_imunity > 0)
		m_imunity--;

	if (m_zCooldown > 0)
		m_zCooldown--;

	std::cout << m_speed.y << std::endl;
}