#include "P9.h"
#include <sstream>

P9::P9()
{
	space1 = new Spaceship1(D3DXVECTOR3(WIN_WIDTH / 2, WIN_HEIGHT / 2, 0.0f));
	space2 = new Spaceship2(D3DXVECTOR3((WIN_WIDTH / 2) - 100, WIN_HEIGHT / 2, 0.0f));

	space1->mass = 2;
	space2->mass = 1;
}

P9::~P9()
{
	delete space1;
	delete space2;
}

void P9::init()
{
	GameGraphics* gGraphics = GameGraphics::getInstance();
	space1->Initialize(gGraphics->d3dDevice);
	space2->Initialize(gGraphics->d3dDevice);
}

void P9::update()
{

}

void P9::fixedUpdate()
{
	if (!(space1->position.x < 0 || space1->position.x > WIN_WIDTH || space1->position.y < 0 || space1->position.y > WIN_HEIGHT))
	{
		space1->Update();
	}
	else
	{
		std::cout << "Player1 lose" << std::endl;
	}

	if (!(space2->position.x < 0 || space2->position.x > WIN_WIDTH || space2->position.y < 0 || space2->position.y > WIN_HEIGHT))
	{
		space2->Update();
	}
	else
	{
		std::cout << "Player2 lose" << std::endl;
	}






	GameInput* gInput = GameInput::getInstance();

	if (isCollide())
	{
		space1->forceTransform(space2);
		std::cout << "Collide" << std::endl;
	}

	if (gInput->KeyboardKeyHold(DIK_A))
	{
		space1->rotate(-1);
	}
	else if (gInput->KeyboardKeyHold(DIK_D))
	{
		space1->rotate(1);
	}
	if (gInput->KeyboardKeyHold(DIK_W))
	{
		space1->acc(1);
	}
	else if (gInput->KeyboardKeyHold(DIK_S))
	{
		space1->acc(-1);
	}


	if (gInput->KeyboardKeyHold(DIK_LEFT))
	{
		space2->rotate(-1);
	}
	else if (gInput->KeyboardKeyHold(DIK_RIGHT))
	{
		space2->rotate(1);
	}
	if (gInput->KeyboardKeyHold(DIK_UP))
	{
		space2->acc(1);
	}
	else if (gInput->KeyboardKeyHold(DIK_DOWN))
	{
		space2->acc(-1);
	}
}

void P9::draw()
{
	std::string space1Detail = "Velocity :" + std::to_string(round(space1->velocity.x)).substr(0, 5) +"|"+ std::to_string(round(space1->velocity.y)).substr(0, 5) + "||"
		+ "Mass :" + std::to_string(space1->mass).substr(0, 5) + "||" + "Force : " + std::to_string(space1->force).substr(0, 5);
	std::string space2Detail = "Velocity :" + std::to_string(round(space2->velocity.x)).substr(0, 5) + "|" + std::to_string(round(space2->velocity.y)).substr(0, 5) + "||"
		+ "Mass :" + std::to_string(space2->mass).substr(0, 5) + "||" + "Force : " + std::to_string(space2->force).substr(0, 5);
	space1->Draw(space1Detail, 255, 255, 255);
	space2->Draw(space2Detail, 200, 200, 200);
}

void P9::release()
{

}

void P9::loadScene()
{
	GameGraphics* gGraphics = GameGraphics::getInstance();

	gGraphics->r = 0;
	gGraphics->g = 128;
	gGraphics->b = 128;
}

bool P9::isCollide()
{
	D3DXVECTOR3 offset = space2->position - space1->position;
	std::cout << D3DXVec3Length(&offset) <<std::endl;
	return D3DXVec3Length(&offset) <= 32;
}
