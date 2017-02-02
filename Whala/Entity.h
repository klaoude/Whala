#pragma once

#include <glm/glm.hpp>

#include <KlaoudeEngine\SpriteBatch.h>
#include <KlaoudeEngine\InputManager.h>
#include <KlaoudeEngine/TileSheet.h>

class Player;

enum class MoveState
{
	STANDING,
	RUNNING,
	PUNCHING,
	IN_AIR
};

class Entity
{
public:
	Entity(int sizeX, int sizeY, float health, float imunity = -1);
	virtual ~Entity();

	virtual void update(const std::vector<std::string>& levelData, float deltaTime, Player* player);

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithEntity(Entity* entity);

	glm::vec2 getPosition() const { return m_position; }
	float getSizeX() const { return m_sizeX; }
	float getSizeY() const { return m_sizeY; }
	bool takeDamage(float damage);

protected:
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

	bool isGrounded(const std::vector<std::string>& levelData);
	bool checkTileGround(glm::vec2 tilePos);
	bool checkTileTop(glm::vec2 tilePos);

	bool isPlafon(const std::vector<std::string>& levelData);

	void applyForce(float deltaTime, const std::vector<std::string>& levelData);

	void jump(float deltaTime, const std::vector<std::string>& levelData, KlaoudeEngine::InputManager* inputManager = nullptr);

	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.f, 0.f);
	glm::vec2 m_speed;
	
	KlaoudeEngine::ColorRGBA8 m_color;
	KlaoudeEngine::TileSheet m_texture;

	//Animation
	MoveState m_moveState = MoveState::STANDING;
	float m_animTime = 0.f;
	int m_dir = 1;

	int m_sizeX;
	int m_sizeY;

	float m_gravity;
	float m_jumpForce;
	float m_dJumpForce;
	int m_jumpTime;
	int m_imunity = 0;
	int m_health = 100;
	int m_maxhealth = 100;

	bool m_isJumping = false;
	bool m_onGround = false;
};

