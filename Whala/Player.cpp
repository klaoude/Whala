#include "Player.h"

#include <SDL/SDL.h>
#include <iostream>

#include <KlaoudeEngine/RessourceManager.h>

Player::Player() : m_inputManager(nullptr)
{
}


Player::~Player()
{
}

void Player::init(float speed,
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

void Player::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, 15, 20);

	spritebatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}

void Player::update(float deltaTime)
{
	if (m_inputManager->isKeyDown(SDLK_s))
		m_position.y -= m_speed * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_z))
		m_position.y += m_speed * deltaTime;
	if (m_inputManager->isKeyDown(SDLK_q))
		m_position.x -= m_speed * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_d))
		m_position.x += m_speed * deltaTime;

	m_direction = glm::vec2(1, 0);
}