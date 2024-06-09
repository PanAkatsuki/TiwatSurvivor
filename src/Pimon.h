#pragma once
#include <graphics.h>

#include "Global.h"
#include "Animation.h"

class Pimon
{
public:
	// Frame
	const int FRAME_LENGTH = 80;
	const int FRAME_HEIGHT = 80;
	const int SHADOW_LENGTH = 32;
	const int SHADOW_HEIGHT = 20;
private:
	// Animation
	Animation* AnimeShadow;
	Animation* AnimeLeft;
	Animation* AnimeRight;
public:
	// Default
	enum class Direction { left, right };
private:
	POINT m_Pos;
	Direction m_Direction;
	POINT m_ShadowPos;
	unsigned int m_Speed;
	bool isMoveUp;
	bool isMoveDown;
	bool isMoveLeft;
	bool isMoveRight;
	unsigned int score;
public:
	// Constructor
	Pimon();
	~Pimon();

	// Default
	Direction GetDirection() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetShadowPosX() const;
	int GetShadowPosY() const;
	unsigned int GetScore() const;

	// Event
	void ProcessEvent(ExMessage& msg);
	void Move();
	void ScorePlus();

	// Rend
	void Rend();
	void DrawScore();
};

