#include "Hud.h"
#include <KlaoudeEngine\RessourceManager.h>
#include "Player.h"

Hud::Hud(float w, float h)
{
	m_texture = KlaoudeEngine::RessourceManager::getTexture("Textures/whitePixel.png").id;

	m_width = w;
	m_height = h;
}



void Hud::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glm::vec4 destRect = glm::vec4(m_height*10/100, m_width * 10 / 100, m_player->getHealth()*3, 10.0f);

	spriteBatch.draw(destRect, uvRect, m_texture, 0.f, KlaoudeEngine::ColorRGBA8(255, 255, 255, 255));
}