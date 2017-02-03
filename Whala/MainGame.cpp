#include "MainGame.h"

#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <glm/gtx/rotate_vector.hpp>

#include <KlaoudeEngine\KlaoudeEngine.h>
#include <KlaoudeEngine\Timing.h>
#include <KlaoudeEngine\RessourceManager.h>

MainGame::MainGame() :
	m_screenWidth(800),
	m_screenHeight(600),
	m_fps(0),
	m_gameState(GameState::PLAY)
{}

MainGame::~MainGame()
{
	for each (Level* level in m_levels)
	{
		delete(level);
	}
}

void MainGame::run()
{
	initSystems();
	initLevel();

	gameLoop();
}

void MainGame::initSystems()
{
	KlaoudeEngine::init();

	m_window.create("test Engine Game", m_screenWidth, m_screenHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	initShaders();

	m_entitySpriteBatch.init();
	m_hudSpriteBatch.init();

	m_spriteFont = new KlaoudeEngine::SpriteFont("Fonts/comic.ttf", 32);

	m_camera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.init(m_screenWidth, m_screenHeight);
	m_hudCamera.setPosition(glm::vec2(m_screenWidth / 2, m_screenHeight / 2));
	m_hud = new Hud(m_screenWidth, m_screenHeight);
}

void MainGame::initLevel()
{
	m_levels.push_back(new Level("Levels/01.txt"));

	m_player = new Player();
	glm::vec2 speed(0, 0);
	m_player->init(speed, glm::vec2(1000, 750), &m_attacks, &m_inputManager, &m_camera);
	m_hud->setPlayer(m_player);
	
	m_enemies.push_back(new Enemi());
	m_enemies[0]->init(speed, glm::vec2(750, 750));

	m_items.push_back(new MagicBook());
	((MagicBook*)m_items[0])->init(glm::vec2(700, 725));
}

void MainGame::initShaders()
{
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}

void MainGame::gameLoop()
{
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;

	KlaoudeEngine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(0.0f);

	const float MS_PER_SEC = 1000.0f;
	const float DESIRED_FRAMETIME = MS_PER_SEC / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;

	float previousTicks = SDL_GetTicks();

	while (m_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();

		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
		
		m_inputManager.update();

		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);

			updateEntity(deltaTime);
			updateAttack(deltaTime);
			updateItem();

			m_player->update(m_levels[0]->getLevelData(), deltaTime, m_player);

			totalDeltaTime -= deltaTime;
			i++;
		}		

		m_camera.setPosition(m_player->getPosition());
		m_camera.update();

		m_hudCamera.update();	

		drawGame();

		m_fps = fpsLimiter.end();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	
	m_levels[0]->draw();

	m_entitySpriteBatch.begin();

	m_player->draw(m_entitySpriteBatch);

	for each(Enemi* enemi in m_enemies)
		enemi->draw(m_entitySpriteBatch);

	for each(Attack att in m_attacks)
		att.draw(m_entitySpriteBatch);

	for each(Item* it in m_items)
		it->draw(m_entitySpriteBatch);

	m_entitySpriteBatch.end();

	m_entitySpriteBatch.renderBatch();

	drawHud();

	m_textureProgram.unUse();

	m_window.swapBuffer();
}

void MainGame::drawHud()
{
	char pos[256], fps[256];

	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	sprintf(pos, "Position : (%f, %f)", m_player->getPosition().x, m_player->getPosition().y);
	sprintf(fps, "FPS : %f", m_fps);

	m_hudSpriteBatch.begin();
	
	m_spriteFont->draw(m_hudSpriteBatch, pos, glm::vec2(0.f, m_screenHeight - 30.f), glm::vec2(0.5f), 0.f, KlaoudeEngine::ColorRGBA8(255, 255, 255, 255));
	m_spriteFont->draw(m_hudSpriteBatch, fps, glm::vec2(0.f, m_screenHeight - 50.f), glm::vec2(0.5f), 0.f, KlaoudeEngine::ColorRGBA8(255, 255, 255, 255));

	m_hud->draw(m_hudSpriteBatch);

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}

void MainGame::updateEntity(float deltaTime)
{
	for each(Enemi* enemi in m_enemies)
		enemi->update(m_levels[0]->getLevelData(), deltaTime, m_player);

	for (auto i = 0; i < m_enemies.size(); i++)
	{
		for (auto j = i + 1; j < m_enemies.size(); j++)
		{
			m_enemies[i]->collideWithEntity(m_enemies[j]);
		}
		if (m_enemies[i]->collideWithEntity(m_player))
			m_player->takeDamage(5.f);
	}
}

void MainGame::updateAttack(float deltaTime)
{
	for (int i = 0; i < m_attacks.size();)
	{
		if (m_attacks[i].update(m_levels[0]->getLevelData(), deltaTime))
		{
			m_attacks[i] = m_attacks.back();
			m_attacks.pop_back();
		}
		else
			i++;
	}

	for (int i = 0; i < m_attacks.size(); i++)
	{
		for (int j = 0; j < m_enemies.size();)
		{
			if (m_attacks[i].collideWithEntity(m_enemies[j]))
			{
				if (m_enemies[j]->takeDamage(m_attacks[i].getDamage()))
				{
					delete m_enemies[j];
					m_enemies[j] = m_enemies.back();
					m_enemies.pop_back();
				}

				m_attacks[i] = m_attacks.back();
				m_attacks.pop_back();
				i--;

				break;
			}
			j++;
		}
	}
}

void MainGame::updateItem()
{
	for (int i = 0; i < m_items.size(); i++)
	{
		if (m_items[i]->update(m_player))
		{
			m_items[i]->applyEffect(m_player);
			m_items[i] = m_items.back();
			m_items.pop_back();
			break;
		}
	}
}