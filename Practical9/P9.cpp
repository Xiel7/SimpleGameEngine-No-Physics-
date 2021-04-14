#include "P9.h"

void P9::init()
{

}

void P9::update()
{
}

void P9::fixedUpdate()
{
}

void P9::draw()
{
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
