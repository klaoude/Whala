#include "Hud.h"
#include <KlaoudeEngine\RessourceManager.h>
#include "Player.h"

Hud::Hud()
{
	m_color = KlaoudeEngine::ColorRGBA8(0, 0, 0, 255);
}

void Hud::init()
{
	m_texture = KlaoudeEngine::RessourceManager::getTexture("Textures/whitePixel.png").id;	
}

void Hud::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glm::vec4 destRect = glm::vec4(100.0f, 300.0f, m_player->getHealth()*3, 10.0f);

	spriteBatch.draw(destRect, uvRect, m_texture, 0.f, m_color);
}