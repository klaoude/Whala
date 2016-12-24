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

void Player::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	const glm::vec4 uvRect(0.f, 0.f, 0.1f, 0.5f);

	glm::vec4 destRect(m_position.x, m_position.y, 15, 20);

	spritebatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color, m_direction);
}

void Player::update(float deltaTime)
{


	if (m_inputManager->isKeyDown(SDLK_s))
		m_acc.y -= 2;
	else if (m_inputManager->isKeyDown(SDLK_z))
		jump(deltaTime);
	if (m_inputManager->isKeyDown(SDLK_q))
		m_acc.x -= 2;
	else if (m_inputManager->isKeyDown(SDLK_d))
		m_acc.x += 2;

	applyForce(deltaTime);
	
	m_direction = glm::vec2(1, 0);
}

void Player::applyForce(float deltaTime)
{
	m_acc.y += gravity;
	m_speed += m_acc;
	m_position += m_speed;
}



void Player::jump(float deltaTime)
{	
	
}