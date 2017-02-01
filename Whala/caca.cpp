#include "caca.h"
#include <KlaoudeEngine\RessourceManager.h>

caca::caca()
{
	m_color = KlaoudeEngine::ColorRGBA8(255, 255, 255, 255);
	m_texture = KlaoudeEngine::RessourceManager::getTexture("Textures/whitePixel.png").id;
}

caca::~caca()
{
}

void caca::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect = glm::vec4(10, 10, 100, 100);
	glm::vec4 uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);

	spriteBatch.draw(destRect, uvRect, m_texture, 0.f, m_color);
}
