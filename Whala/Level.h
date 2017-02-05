#pragma once

#include <string>
#include <vector>

#include<KlaoudeEngine\SpriteBatch.h>

const float TILE_WIDTH = 24;

class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();

	const std::vector<std::string>& getLevelData() const { return m_levelData; }

private:
	std::vector<std::string> m_levelData;
	KlaoudeEngine::SpriteBatch m_spriteBatch;
};