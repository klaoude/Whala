#pragma once

#include <glm/glm.hpp>

#include <KlaoudeEngine\SpriteBatch.h>

class Entity
{
public:
	Entity(int sizeX, int sizeY);
	virtual ~Entity();

	virtual void update(const std::vector<std::string>& levelData, float deltaTime) = 0;

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	bool collideWithLevel(const std::vector<std::string>& levelData);

	glm::vec2 getPosition() const { return m_position; }

protected:
	void checkTilePosition(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y);
	void collideWithTile(glm::vec2 tilePos);

	bool isGrounded(const std::vector<std::string>& levelData);
	bool checkTile(glm::vec2 tilePos);

	bool isPlafon(const std::vector<std::string>& levelData);

	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.f, 0.f);
	float m_speed;
	KlaoudeEngine::ColorRGBA8 m_color;
	GLuint m_textureID;

	int m_sizeX;
	int m_sizeY;
};

