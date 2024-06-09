#pragma once

#include <graphics.h>
#include "Pimon.h"

class Bullet
{
private:
	int RADIUS = 10;
	POINT m_Pos;
public:
	Bullet(Pimon& pimon);
	~Bullet();

	int GetPosX() const;
	int GetPosY() const;
	void ChangePosX(int x);
	void ChangePosY(int y);

	void Rend();
};

