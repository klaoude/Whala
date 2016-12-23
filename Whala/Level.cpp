#include "Level.h"

#include <fstream>
#include <KlaoudeEngine\Errors.h>
#include <KlaoudeEngine\RessourceManager.h>

Level::Level(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.fail())
		KlaoudeEngine::fatalError("Failled to open " + fileName);

	std::string tmp;
	
	while (std::getline(file, tmp))
	{
		m_levelData.push_back(tmp);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
	KlaoudeEngine::ColorRGBA8 whiteColor(255, 255, 255, 255);

	for (int y = 0; y < m_levelData.size(); y++)
	{
		for (int x = 0; x < m_levelData[y].size(); x++)
		{
			char tile = m_levelData[y][x];

			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile)
			{
			case 'W':
				m_spriteBatch.draw(destRect, uvRect, KlaoudeEngine::RessourceManager::getTexture("Textures/red_bricks.png").id, 0.f, whiteColor);
				break;
			default:
				break;
			}
		}
	}
	m_spriteBatch.end();
}

Level::~Level()
{
}

void Level::draw()
{
	m_spriteBatch.renderBatch();
}