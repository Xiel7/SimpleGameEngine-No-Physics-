#pragma once
#include "GameObject.h"


class Spaceship1 : public GameObject
{
private:

public:

	Spaceship1();
	Spaceship1(D3DXVECTOR3 position);
	~Spaceship1();

	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update();
	void rotate(float value);
	void acc(float value);

	void resolveCollision();

	void forceTransform(GameObject* object);

	void Draw(std::string msg, int r, int g, int b);

};

