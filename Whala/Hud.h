#pragma once
#include <klaoudeengine\spritebatch.h>
#include <KlaoudeEngine/TileSheet.h>

class Player;

class Hud
{
public:
	Hud();
	
	void init();
	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

	void setPlayer(Player *player) { m_player = player;  }


private:
	Player *m_player;
	glm::vec4 m_uvRect, m_destRect;
	GLuint m_texture;
	KlaoudeEngine::ColorRGBA8 m_color;

};