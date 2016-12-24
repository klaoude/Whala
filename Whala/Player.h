#pragma once
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine\SpriteBatch.h>

const float SIZE_X = 16;
const float SIZE_Y = 20;

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

	void update(float deltaTime, const std::vector<std::string>& levelData);

	bool collideWithLevel(const std::vector<std::string>& levelData);
	void jump(float deltaTime);
	void applyForce(float deltaTime);
	void update(float deltaTime);

	glm::vec2 getPosition() { return m_position; }

private:
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

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