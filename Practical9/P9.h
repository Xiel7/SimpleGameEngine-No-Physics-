#pragma once
#include "GameState.h"
#include "GameGraphics.h"

class P9 : public GameState
{

public:
	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	void loadScene();
};

