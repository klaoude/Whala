#pragma once
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine\SpriteBatch.h>

#include "Entity.h"
#include "Attack.h"

const float SIZE_X = 16;
const float SIZE_Y = 20;

class Player : public Entity
{
public:
	Player();
	~Player();

	void init(glm::vec2 speed,
		glm::vec2 position,
		std::vector<Attack>* attacks,
		KlaoudeEngine::InputManager* inputManager,
		KlaoudeEngine::Camera2D* camera);

	void update(const std::vector<std::string>& levelData, float deltaTime, Player* player) override;

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	int getHealth() { return m_health; }
	int getMaxHealth() { return m_maxhealth; }
	float getAttackSpeed() { return m_attackSpeed; }
	float getzCoolCur() 
	{ 
		if (m_zCooldown - m_frameCounter > 0)
			return m_zCooldown - m_frameCounter;
		return 0;
	}
	float getzCoolMax() { return m_zCooldown; }

	void addAttackSpeed(float value) { m_attackSpeed += value; }

private:
	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;	

	std::vector<Attack>* m_attacks;

	float m_attackSpeed;
	float m_zCooldown;
	float m_frameCounter;
};