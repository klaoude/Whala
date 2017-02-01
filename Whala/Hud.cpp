#include "Hud.h"
#include <KlaoudeEngine\RessourceManager.h>
#include "Player.h"

Hud::Hud()
{
}

void Hud::init()
{
	m_texture = KlaoudeEngine::RessourceManager::getTexture("Textures/whitePixel.png");

	m_uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	m_destRect = glm::vec4(100.0f, 300.0f, 300.0f, 10.0f);
}

void Hud::draw(KlaoudeEngine::SpriteBatch& spritebatch)
{
	m_destRect = glm::vec4(100.0f, 300.0f, m_player->getHealth()*3, 10.0f);
	spritebatch.draw(m_destRect, m_uvRect, m_texture.id, 0.f, KlaoudeEngine::ColorRGBA8(255, 255, 255, 255));
}