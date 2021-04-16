#include "Spaceship2.h"


Spaceship2::Spaceship2()
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32, 32, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	mat = D3DMATRIX();


	animationCount = 2;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 1;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

}

Spaceship2::Spaceship2(D3DXVECTOR3 position)
{
	texture = NULL;
	sprite = NULL;

	scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	size = D3DXVECTOR3(32, 32, 1.0f);
	spriteCentre = D3DXVECTOR3(size.x / 2, size.y / 2, 0.0f);
	this->position = position;
	mat = D3DMATRIX();


	animationCount = 2;
	animationCountCol = 2;
	animationTimer = 0;
	animationRate = 0.1f / animationCount * animationCountCol;
	currentFrame = 1;
	animationRow = 0;
	animationLoop = true;

	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;

	direction.x = 0;
	direction.y = 0;
}

Spaceship2::~Spaceship2()
{

}

void Spaceship2::Initialize(LPDIRECT3DDEVICE9 device)
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

void Spaceship2::Update()
{

	position += (velocity / 60.0);


	animationTimer += 1 / 60.0f;
	if (animationTimer >= animationRate)
	{
		animationRow++;
		if (animationRow >= animationCountCol)
		{
			animationRow %= animationCountCol;
		}
	}

	spriteRect.top = size.y * animationRow;
	spriteRect.left = size.x * currentFrame;
	spriteRect.bottom = spriteRect.top + size.y;
	spriteRect.right = spriteRect.left + size.x;
}

void Spaceship2::rotate(float value)
{
	rotationAngle += value;

	float rad = rotationAngle / 180 * 3.142;
	direction.x = sin(rad);
	direction.y = -cos(rad);

	velocity = direction * force;
}

void Spaceship2::acc(float value)
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

void Spaceship2::resolveCollision()
{
	velocity = -velocity / 2;
	force = D3DXVec3Length(&velocity);
	position += velocity / 60;
}

void Spaceship2::Draw(std::string msg, int r, int g, int b)
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	SetTransform();
	font->DrawText(sprite, msg.c_str(), -1, &textRect, DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));
	sprite->Draw(texture, &spriteRect, &spriteCentre, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

}


