#pragma once

#include <graphics.h>

#include "Global.h"
#include "Animation.h"
#include "Pimon.h"
#include "Bullet.h"

class Enemy
{
public:
	// Frame
	const int FRAME_LENGTH = 80;
	const int FRAME_HEIGHT = 80;
	const int SHADOW_LENGTH = 48;
	const int SHADOW_HEIGHT = 30;
private:
	// Animation
	Animation* AnimeShadow;
	Animation* AnimeLeft;
	Animation* AnimeRight;
public:
	// Default
	enum class SpawnEdge
	{
		up = 0,
		down,
		left,
		right
	};
	enum class Direction { left, right };
private:
	POINT m_Pos;
	Direction m_Direction;
	POINT m_ShadowPos;
	unsigned int m_Speed;
	bool m_Alive;
public:
	// Constructor
	Enemy();
	~Enemy();

	// Check
	bool CheckBulletCollision(Bullet& bullet) const;
	bool CheckPimonCollision(Pimon& pimon) const;
	void CheckHurt(Bullet& bullet);
	bool CheckAlive() const;

	// Event
	void Move(Pimon& pimon);

	// Rend
	void Rend();
};

