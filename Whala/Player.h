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
	
private:
	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;	

	std::vector<Attack>* m_attacks;

	int m_zCooldown = 0;
};