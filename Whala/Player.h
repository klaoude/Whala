#pragma once
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine\SpriteBatch.h>

class Player
{
public:
	Player();
	~Player();

	void init(glm::vec2 speed,
		glm::vec2 position,
		KlaoudeEngine::InputManager* inputManager,
		KlaoudeEngine::Camera2D* camera);

	void draw(KlaoudeEngine::SpriteBatch& spritebatch);

	void jump(float deltaTime);
	void applyForce(float deltaTime);
	void update(float deltaTime);

	glm::vec2 getPosition() { return m_position; }

private:
	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;

	float gravity = -2;
	glm::vec2 m_acc;
	glm::vec2 m_speed;
	glm::vec2 m_position;
	KlaoudeEngine::ColorRGBA8 m_color;
	glm::vec2 m_direction;
	GLuint m_textureID;
};