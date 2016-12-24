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

	void update(const std::vector<std::string>& levelData, float deltaTime) override;

	void applyForce(float deltaTime, const std::vector<std::string>& levelData);

private:
	bool isGrounded(const std::vector<std::string>& levelData);
	bool checkTile(glm::vec2 tilePos);

	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;

	float gravity;
	glm::vec2 m_acc;
	glm::vec2 m_speed;

	bool m_isJumping = false;
	int time = 0;
	int t0 = 0, t = 0;
	glm::vec2 pos0, speed0;
};