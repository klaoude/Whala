#pragma once
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine\SpriteBatch.h>

class Player
{
public:
	Player();
	~Player();

	void init(float speed,
		glm::vec2 position,
		KlaoudeEngine::InputManager* inputManager,
		KlaoudeEngine::Camera2D* camera);

	void draw(KlaoudeEngine::SpriteBatch& spritebatch);

	void update(float deltaTime);

	glm::vec2 getPosition() { return m_position; }

private:
	KlaoudeEngine::InputManager* m_inputManager;
	KlaoudeEngine::Camera2D* m_camera;

	int m_speed;
	glm::vec2 m_position;
	KlaoudeEngine::ColorRGBA8 m_color;
	glm::vec2 m_direction;
	GLuint m_textureID;
};