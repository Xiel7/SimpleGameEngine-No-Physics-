#pragma once
#include "GameObject.h"

class Spaceship2 : public GameObject
{
private:

public:
	Spaceship2();
	Spaceship2(D3DXVECTOR3 position);
	~Spaceship2();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void rotate(float value);
	void acc(float value);
	void resolveCollision();
	void Draw(std::string msg, int r, int g, int b);
};

