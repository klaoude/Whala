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

private:
	void applyForce(float deltaTime, const std::vector<std::string>& levelData);

	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;

	float gravity;
	glm::vec2 m_speed;
	float m_jumpForce;
	float m_dJumpForce;

	bool m_isJumping = false;
	int time = 0;
	int t0 = 0, t = 0;
	glm::vec2 pos0, speed0;
};