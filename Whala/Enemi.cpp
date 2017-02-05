#include "Enemi.h"
#include <KlaoudeEngine\RessourceManager.h>
#include <time.h>
#include "Level.h"
#include "Player.h"

Enemi::Enemi() : Entity(16, 20, 20){ m_randomEngine.seed(time(nullptr)); }

Enemi::~Enemi(){}

void Enemi::init(glm::vec2 speed, glm::vec2 position)
{
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_int_distribution<int> randDir(-1, 1);

	m_speed = speed;
	m_position = position;

	m_direction = glm::vec2(1.0f, 0.0f);

	m_color = KlaoudeEngine::ColorRGBA8(255, 0, 0, 255);
	KlaoudeEngine::GLTexture texture = KlaoudeEngine::RessourceManager::getTexture("Textures/Player.png");
	m_texture.init(texture, glm::ivec2(10, 2));
}

void Enemi::update(const std::vector<std::string>& levelData, float deltaTime, Player* player)
{
	m_onGround = false;
	if (isGrounded(levelData))
		m_onGround = true;

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_int_distribution<int> randDir(-1, 1);
	static std::uniform_int_distribution<int> randJump(0, 1);

	applyForce(deltaTime);

	glm::vec2 distVec = player->getPosition() - m_position;
	float distance = glm::length(distVec);

	if (distance < 200)
	{
		glm::vec2 direction = glm::normalize(player->getPosition() - m_position);
		m_position.x += direction.x * 3.f * deltaTime;
	}
	else
	{
		m_position -= m_dir * 3.f * deltaTime;

		if (m_frame >= 60 * 5)
		{
			if (randJump(randomEngine) == 1)
				jump(deltaTime, levelData);

			m_dir = randDir(randomEngine);
			m_frame = 0;
		}		
	}	

	collideWithLevel(levelData);

	m_frame++;
}

char Enemi::getLeftCase(const std::vector<std::string>& levelData)
{
	glm::vec2 cornerPos = glm::vec2(floor(m_position.x / float(TILE_WIDTH)),
		floor(m_position.y / float(TILE_WIDTH)));

	if (cornerPos.x < 1 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 1 || cornerPos.y >= levelData.size())
		return ' ';

	return levelData[cornerPos.y - 1][cornerPos.x - 1];
}

char Enemi::getRightCase(const std::vector<std::string>& levelData)
{
	glm::vec2 cornerPos = glm::vec2(floor(m_position.x + m_sizeX / float(TILE_WIDTH)),
		floor(m_position.y / float(TILE_WIDTH)));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() - 1 ||
		cornerPos.y < 1 || cornerPos.y >= levelData.size())
		return ' ';

	return levelData[cornerPos.y - 1][cornerPos.x + 1];
}