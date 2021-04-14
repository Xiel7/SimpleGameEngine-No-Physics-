#pragma once
#include "GameState.h"
#include "GameTimer.h"
#include "P9.h"
#include <vector>
#include <iostream>
#define FPS 60.0f

class GameStateManager
{
private:

	static GameStateManager* instance;
	GameStateManager();
	~GameStateManager();
public:
	static GameStateManager* getInstance();
	void fixedUpdate();
	void update();
	void draw();
	void release();

	float elapsedTime;
	int levelContinue;
	//test

	GameTimer* gTimer;
	GameState* currentGameState;
	GameState* tempGameState;
	std::vector<GameState*> gameLevels;
	void changeGameState(int index);

};