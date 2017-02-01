#include "Item.h"

#include "Player.h"

Item::Item(int sizeX, int sizeY, float scale)
{
	m_sizeX = sizeX / scale;
	m_sizeY = sizeY / scale;

	m_color = KlaoudeEngine::ColorRGBA8(255, 255, 255, 255);
}

Item::~Item()
{
}

void Item::draw(KlaoudeEngine::SpriteBatch & spriteBatch)
{
	glm::vec4 uvRect = m_texture.getUVs(0);
	glm::vec4 destRect(m_position.x, m_position.y, m_sizeX, m_sizeY);

	spriteBatch.draw(destRect, uvRect, m_texture.texture.id, m_scale, m_color, m_direction);
}

void Item::applyEffect(Player* player)
{
	player->addAttackSpeed(5.f);
}

bool Item::collideWithPlayer(Player * player)
{
	const float MIN_DIST_X = m_sizeX / 2.f;
	const float MIN_DIST_Y = m_sizeY / 2.f;

	glm::vec2 centerPosA = m_position + glm::vec2(m_sizeX / 2.f, m_sizeY / 2.f);
	glm::vec2 centerPosB = player->getPosition() + glm::vec2(player->getSizeX() / 2.f, player->getSizeY() / 2.f);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepthX = MIN_DIST_X - distance;
	float collisionDepthY = MIN_DIST_Y - distance;

	if (collisionDepthX > 0)
	{
		return true;
	}
	else if (collisionDepthY > 0)
	{
		return true;
	}

	return false;
}
