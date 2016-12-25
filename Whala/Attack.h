#pragma once
#include <KlaoudeEngine\SpriteBatch.h>

class Entity;

class Attack
{
public:
	Attack(glm::vec2 position, glm::vec2 direction, float speed, float damage, float sizeX, float sizeY, int lifeTime = -1);
	~Attack();

	bool update(const std::vector<std::string>& levelData, float deltaTime);

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	bool collideWithEntity(Entity* entity);

	float getDamage() { return m_damage; }
	glm::vec2 getPosition() { return m_position; }

private:
	bool CollideWithWorld(const std::vector<std::string>& levelData);

	glm::vec2 m_position;
	glm::vec2 m_direction;

	float m_speed;
	float m_damage;

	float m_sizeX;
	float m_sizeY;

	int m_lifeTime;
};