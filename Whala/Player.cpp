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
	if (m_inputManager->isKeyDown(SDLK_q))
	{
		m_speed.x = -4 * deltaTime;
	}
	else if (m_inputManager->isKeyDown(SDLK_d))
	{
		m_speed.x = 4 * deltaTime;
	}
	if (m_inputManager->isKeyDown(SDLK_s))
		m_position.y -= m_speed.x * deltaTime;

	else if (m_inputManager->isKeyDown(SDLK_z))
		m_isJumping = true;

	jump(deltaTime, levelData);

	applyForce(deltaTime, levelData);

	collideWithLevel(levelData);	

	std::cout << m_speed.y << std::endl;
}

void Player::jump(float deltaTime, const std::vector<std::string>& levelData)
{
	m_jumpForce = 0.5f * deltaTime;
	if (m_isJumping)
	{
		m_jumpTime++;

		if (m_jumpTime < 100 && m_inputManager->isKeyDown(SDLK_z))
			m_speed.y += 0.1 * deltaTime;

		if (m_dJumpForce > 0)
			m_dJumpForce -= 0.1 * deltaTime;
		else
			m_dJumpForce = 0;
	}
	else
	{
		m_dJumpForce = m_jumpForce;
		m_jumpTime = 0;
	}
	if (isGrounded(levelData) && m_dJumpForce == 0)
	{
		m_isJumping = false;
		m_speed.y = 0;
		m_dJumpForce = 0;
	}
	else if (isGrounded(levelData) && !m_isJumping)
		m_speed.y = 0;
	if (isPlafon(levelData))
	{
		m_speed.y = 0;
		m_dJumpForce = 0;
	}
}
