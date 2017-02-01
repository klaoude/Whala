#include "Hud.h"
#include <KlaoudeEngine\RessourceManager.h>
#include "Player.h"

Hud::Hud(float w, float h)
{
	m_hudTexture = KlaoudeEngine::RessourceManager::getTexture("Textures/hud.png").id;

	m_width = w;
	m_height = h;
}



void Hud::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glm::vec4 destRect = glm::vec4(m_width / 2 - 160, m_height*10/100, 320.f, 112.f);

	spriteBatch.draw(destRect, uvRect, m_hudTexture, 0.f, c_white);
}