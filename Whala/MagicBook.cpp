#include "MagicBook.h"

#include <KlaoudeEngine\RessourceManager.h>

MagicBook::MagicBook() : Item(59, 59, 2.f)
{
}

MagicBook::~MagicBook()
{
}

void MagicBook::init(glm::vec2 position)
{
	m_position = position;
	KlaoudeEngine::GLTexture texture = KlaoudeEngine::RessourceManager::getTexture("Textures/books_misc0.1.png");
	m_texture.init(texture, glm::ivec2(5, 4));
}

bool MagicBook::update(Player* player)
{
	return collideWithPlayer(player);
}
