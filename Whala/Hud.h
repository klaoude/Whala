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
	GLuint m_hudTexture, m_rectTexture;

	glm::vec4 m_uvRect, m_hudRect, m_lifeBarRect, m_zRect;

	float m_width, m_height, m_mzCool;


	KlaoudeEngine::ColorRGBA8 c_white = KlaoudeEngine::ColorRGBA8(255, 255, 255, 255);
	KlaoudeEngine::ColorRGBA8 c_black = KlaoudeEngine::ColorRGBA8(35, 29, 30, 255);
	KlaoudeEngine::ColorRGBA8 c_grey = KlaoudeEngine::ColorRGBA8(58, 50, 50, 255);

	KlaoudeEngine::ColorRGBA8 c_yellow = KlaoudeEngine::ColorRGBA8(239, 172, 65, 255);
	KlaoudeEngine::ColorRGBA8 c_darkYellow = KlaoudeEngine::ColorRGBA8(222, 133, 49, 255);
	KlaoudeEngine::ColorRGBA8 c_red = KlaoudeEngine::ColorRGBA8(179, 41, 0, 255);
	KlaoudeEngine::ColorRGBA8 c_darkRed = KlaoudeEngine::ColorRGBA8(108, 19, 5, 255);
	KlaoudeEngine::ColorRGBA8 c_darkerRed = KlaoudeEngine::ColorRGBA8(51, 10, 4, 255);
	KlaoudeEngine::ColorRGBA8 c_purple = KlaoudeEngine::ColorRGBA8(96, 72, 96, 255);









};