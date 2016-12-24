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
	m_direction = glm::vec2(1.f, 0.f);
	m_jumpForce = 1.1f * deltaTime;
	if (m_isJumping)
	{
		if (m_dJumpForce > 0)
			m_dJumpForce -= 0.1 * deltaTime;
		else
			m_dJumpForce = 0;
	}
	else
		m_dJumpForce = m_jumpForce;

	if (m_inputManager->isKeyDown(SDLK_s))
		m_position.y -= m_speed.x * deltaTime;

	else if (m_inputManager->isKeyDown(SDLK_z))
		m_isJumping = true;

	if (m_inputManager->isKeyDown(SDLK_q))
	{
		m_speed.x = -4 * deltaTime;
	}
	else if (m_inputManager->isKeyDown(SDLK_d))
	{
		m_speed.x = 4 * deltaTime;
	}

	applyForce(deltaTime, levelData);
	if (isGrounded(levelData) && m_isJumping)
		m_isJumping = false;
	if (isPlafon(levelData))
	{
		m_speed.y = 0;
		m_dJumpForce = 0;
	}

	collideWithLevel(levelData);	
}
