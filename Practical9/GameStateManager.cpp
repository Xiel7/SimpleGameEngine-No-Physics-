#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = 0;

GameStateManager::GameStateManager()
{
	std::cout << "GameStateManager constructed" << std::endl;

	
	P9* p9 = new P9;
	p9->init();
	gameLevels.push_back(p9);

	//TestLevel4* testLevel4 = new TestLevel4;
	//testLevel4->init();
	//gameLevels.push_back(testLevel4); // 4 Level 3

	currentGameState = gameLevels[0];
	tempGameState = currentGameState;
	currentGameState->loadScene();

	gTimer = new GameTimer;
	gTimer->init(FPS);

	elapsedTime = 0;

}

GameStateManager::~GameStateManager()
{
	std::cout << "GameStateManager destroyed" << std::endl;
	for (int i = 0; i < gameLevels.size(); i++)
	{
		delete gameLevels[i];
		gameLevels[i] = NULL;
	}

	currentGameState = NULL;
	delete gTimer;
	gTimer = NULL;

}

GameStateManager* GameStateManager::getInstance()
{
	if (!instance)
	{
		instance = new GameStateManager;
	}

	return instance;
}


void GameStateManager::fixedUpdate()
{
	
	int framesToUpdate = gTimer->framesToUpdate();
	for (int i = 0; i < framesToUpdate; i++)
	{
		elapsedTime += (1.0f / FPS);
		currentGameState->fixedUpdate();
	}

}

void GameStateManager::update()
{
	if (currentGameState != tempGameState)
	{
		currentGameState->loadScene();
		tempGameState = currentGameState;
	}
	currentGameState->update();

}

void GameStateManager::draw()
{
	currentGameState->draw();
}

void GameStateManager::release()
{
	//currentGameState->release();
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}

void GameStateManager::changeGameState(int index)
{
	currentGameState = gameLevels[index];
}
