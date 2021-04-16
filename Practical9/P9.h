#pragma once
#include "GameState.h"
#include "GameGraphics.h"
#include "Spaceship1.h"
#include "Spaceship2.h"


class P9 : public GameState
{
private:
	Spaceship1* space1;
	Spaceship2* space2;

	//bool space1wins;
	//bool space1wins;

public:
	P9();
	~P9();

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	void loadScene();


	bool isCollide();
};

