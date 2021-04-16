#include "Spaceship1.h"

Spaceship1::Spaceship1()
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32, 32, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 1;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

}

Spaceship1::Spaceship1(D3DXVECTOR3 position)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32, 32, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 1;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 0;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	direction.x = 0;
	direction.y = 0;

}

Spaceship1::~Spaceship1()
{

}

void Spaceship1::Initialize(LPDIRECT3DDEVICE9 device)
{
	D3DXCreateSprite(device, &sprite);
	D3DXCreateTextureFromFile(device, "practical9.png", &texture);

	D3DXCreateFont(device, 18, 0, BOLD_FONTTYPE, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	textRect.left = -80;
	textRect.top = -30;
	textRect.right = 80;
	textRect.bottom = 0;
}

void Spaceship1::Update()
{
	//if (force > 0)
	//{
	//	float rad = rotationAngle / 180.0 * 3.142;
	//	direction.x = sin(rad);
	//	direction.y = -cos(rad);


	//	velocity = direction * force;
	//	position += (velocity / 60.0);
	//}

	position += (velocity / 60.0);



	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationRate)
	{
		animationTimer -= animationRate;
		currentFrame++;
		if (animationLoop)
		{
			currentFrame %= animationCount;
			if (currentFrame == 0)
			{
				animationRow++;
				animationRow %= animationCountCol;
			}
		}
		else
		{
			if (currentFrame == animationCount)
			{
				animationRow++;
				currentFrame = 0;

				if (animationRow >= animationCountCol)
				{
					animationRow = animationCountCol;
				}
			}
			if (currentFrame >= animationCount - 1)
			{
				currentFrame = animationCount - 1;
			}
		}

	}

	spriteRect.top = size.y * animationRow;
	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

void Spaceship1::rotate(float value)
{
	rotationAngle += value;

	float rad = rotationAngle / 180 * 3.142;
	direction.x = sin(rad);
	direction.y = -cos(rad);

	velocity = direction * force;
}

void Spaceship1::acc(float value)
{
	if (value > 0)
	{
		force += 1;
		force = min(force, 200);
	}
	else if (value < 0)
	{
		force -= 1;
		force = max(force, 0);
	}

	velocity = direction * force;
}


void Spaceship1::resolveCollision()
{
	velocity = -velocity / 2;
	force = D3DXVec3Length(&velocity);
	position += velocity / 60;
}

void Spaceship1::forceTransform(GameObject* object)
{
	float force1 = this->force * this->mass;
	float force2 = object->force * object->mass;
	this->force = force2/2;
	object->force = force1/2;

	D3DXVECTOR3 velocity1 = this->velocity * this->mass;
	D3DXVECTOR3 velocity2 = object->velocity * object->mass;
	this->velocity = velocity2;
	object->velocity = velocity1;
}

void Spaceship1::Draw(std::string msg, int r, int g, int b)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	font->DrawText(sprite, msg.c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

}