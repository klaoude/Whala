#pragma once
#include <klaoudeengine\spritebatch.h>

class caca
{
public:
	caca();
	~caca();

	void draw(KlaoudeEngine::SpriteBatch& spriteBatch);

private:
	GLuint m_texture;
	KlaoudeEngine::ColorRGBA8 m_color;
};

