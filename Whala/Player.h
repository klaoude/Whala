#pragma once
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine\SpriteBatch.h>

#include "Entity.h"

const float SIZE_X = 16;
const float SIZE_Y = 20;

class Player : public Entity
{
public:
	Player();
	~Player();

	void init(glm::vec2 speed,
		glm::vec2 position,
		KlaoudeEngine::InputManager* inputManager,
		KlaoudeEngine::Camera2D* camera);

	void update(const std::vector<std::string>& levelData, float deltaTime, Player* player) override;

	int getHealth() { return m_health; }
	void takeDamage(float damage);
private:
	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;	

	int m_health = 100;
	int m_imunity = 0;
};