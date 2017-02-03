#include "Hud.h"
#include <KlaoudeEngine\RessourceManager.h>
#include "Player.h"

Hud::Hud(float w, float h)
{
	m_hudTexture = KlaoudeEngine::RessourceManager::getTexture("Textures/hud.png").id;
	m_rectTexture = KlaoudeEngine::RessourceManager::getTexture("Textures/whitePixel.png").id;

	m_width = w;
	m_height = h;

	m_uvRect = glm::vec4(0.f, 0.f, 1.f, 1.f);

	m_hudRect = glm::vec4(m_width / 2 - 160, 0, 322.f, 124.f);
}

void Hud::draw(KlaoudeEngine::SpriteBatch& spriteBatch)
{
	m_lifeBarRect = glm::vec4(m_width / 2 - 154, 107, m_player->getHealth()*310/m_player->getMaxHealth(), 11.f);
	m_zRect = glm::vec4(m_width / 2 - 156, 47, 74, m_player->getzCool() * 52 / m_player->getzCool() - (m_player->getAttackSpeed() - 1.f));
		
	spriteBatch.draw(m_hudRect, m_uvRect, m_hudTexture, 0.f, c_white);

	spriteBatch.draw(m_lifeBarRect, m_uvRect, m_rectTexture, 0.f, c_red);

	spriteBatch.draw(m_zRect, m_uvRect, m_rectTexture, 0.f, c_darkRed);

}