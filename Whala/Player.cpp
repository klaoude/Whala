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
	m_frameCounter = 0.f;
	m_zCooldown = 30.f;
	m_attackSpeed = 1.f;
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

	KlaoudeEngine::GLTexture texture = KlaoudeEngine::RessourceManager::getTexture("Textures/Player.png");
	m_texture.init(texture, glm::ivec2(10, 2));
}

void Player::update(const std::vector<std::string>& levelData, float deltaTime, Player* player)
{
	m_frameCounter += 1.f * deltaTime;
	m_zCooldown = m_zCooldown - (m_attackSpeed - 1.f);

	m_onGround = false;
	if (isGrounded(levelData))
		m_onGround = true;

	if (m_inputManager->isKeyDown(SDLK_LEFT))
	{
		m_speed.x = -4 * deltaTime;
		m_dir = -1;
	}
	else if (m_inputManager->isKeyDown(SDLK_RIGHT))
	{
		m_speed.x = 4 * deltaTime;
		m_dir = 1;
	}
	if (m_inputManager->isKeyDown(SDLK_DOWN))
		m_position.y -= m_speed.x * deltaTime;
	else if (m_inputManager->isKeyDown(SDLK_UP))
	{
		if (!m_isJumping)
			m_speed.y += 1 * deltaTime;
		m_isJumping = true;
	}
	if (m_frameCounter >= m_zCooldown && m_inputManager->isKeyDown(SDLK_z))
	{
		if (m_dir == -1)
			m_attacks->push_back(Attack(glm::vec2(m_position.x - m_sizeX - 8.f, m_position.y + m_sizeY / 2.f - 8.f * 2.f),
				glm::vec2(1.f, 0.f), 10.f, 10.f, 8.f, 8.f, true, 25));
		else
			m_attacks->push_back(Attack(glm::vec2(m_position.x + m_sizeX, m_position.y + m_sizeY / 2.f - 8.f * 2.f),
				glm::vec2(1.f, 0.f), 10.f, 10.f, 8.f, 8.f, false, 25));

		m_frameCounter = 0.f;
	}		

	jump(deltaTime, levelData, m_inputManager);	

	applyForce(deltaTime);

	collideWithLevel(levelData);

	if (m_imunity > 0)
		m_imunity--;
}

void Player::draw(KlaoudeEngine::SpriteBatch & spriteBatch)
{	
	std::cout << m_isJumping << std::endl;

	glm::vec4 destRect(m_position.x, m_position.y, m_sizeX, m_sizeY);

	int tileIndex;
	int numTiles;

	float animationSpeed = 0.2f;

	if (m_onGround)
	{
		if (abs(m_speed.x) > 0.f)
		{
			numTiles = 6;
			tileIndex = 10;
			animationSpeed = 0.08f;
			if (m_moveState != MoveState::RUNNING)
			{
				m_moveState = MoveState::RUNNING;
				m_animTime = 0;
			}
		}
		else if(m_speed.x == 0.f)
		{
			tileIndex = 0;
			numTiles = 1;
			m_moveState = MoveState::STANDING;
		}
	}
	else
	{
		if (m_speed.y <= 0.f)
		{
			numTiles = 1;
			tileIndex = 17;
			m_moveState = MoveState::IN_AIR;
		}
		else
		{
			numTiles = 1;
			tileIndex = 16;
			m_moveState = MoveState::IN_AIR;
		}
	}

	m_animTime += animationSpeed;

	tileIndex = tileIndex + (int)m_animTime % numTiles;

	glm::vec4 uvRect = m_texture.getUVs(tileIndex);

	if (m_dir == -1)
	{
		uvRect.x += 1.f / m_texture.dims.x;
		uvRect.z *= -1;
	}

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, 0.0f, m_color, m_direction);

	m_speed.x = 0.f;
}