#pragma once

#include <KlaoudeEngine\SpriteBatch.h>
#include <KlaoudeEngine\TileSheet.h>

class Player;

class Item
{
public:
	Item(int sizeX, int sizeY, float scale);
	~Item();

	virtual bool update(Player* player) = 0;

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

protected:
	bool collideWithPlayer(Player* player);

	glm::vec2 m_position;
	glm::vec2 m_direction = glm::vec2(1.f, 0.f);

	KlaoudeEngine::ColorRGBA8 m_color;
	KlaoudeEngine::TileSheet m_texture;

	int m_sizeX;
	int m_sizeY;
	float m_scale;
};

