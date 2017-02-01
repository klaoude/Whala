#pragma once
#include <klaoudeengine\spritebatch.h>
#include <KlaoudeEngine/TileSheet.h>

class Player;

class Hud
{
public:
	Hud(float width, float height);
	
	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	void setPlayer(Player *player) { m_player = player;  }


private:
	Player *m_player;
	GLuint m_texture;

	glm::vec4 m_uvRect, m_destRect;

	float m_width, m_height;





};