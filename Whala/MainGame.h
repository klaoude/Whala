#pragma once

#include <KlaoudeEngine/Window.h>
#include <KlaoudeEngine/GLSLProgram.h>
#include <KlaoudeEngine/Camera2D.h>
#include <KlaoudeEngine/InputManager.h>
#include <KlaoudeEngine/SpriteBatch.h>
#include <KlaoudeEngine\SpriteFont.h>

#include "Player.h"
#include "Level.h"
#include "Enemi.h"

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initLevel();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	void drawHud();
	void updateEntity(float deltaTime);

	KlaoudeEngine::Window m_window;
	KlaoudeEngine::GLSLProgram m_textureProgram;
	KlaoudeEngine::InputManager m_inputManager;
	KlaoudeEngine::Camera2D m_camera;
	KlaoudeEngine::Camera2D m_hudCamera;
	KlaoudeEngine::SpriteBatch m_entitySpriteBatch;
	KlaoudeEngine::SpriteBatch m_hudSpriteBatch;
	KlaoudeEngine::SpriteFont* m_spriteFont;

	int m_screenWidth, m_screenHeight;
	float m_fps;
	int m_currentLevel;

	GameState m_gameState;

	Player* m_player;
	std::vector<Enemi*> m_enemies;

	std::vector<Level*> m_levels;
};