#pragma once
#include <graphics.h>


class AController
{
public:
	AController();
	~AController();

protected:
	bool bIsMoveUp = false;
	bool bIsMoveDown = false;
	bool bIsMoveLeft = false;
	bool bIsMoveRight = false;

public:
	inline bool GetbIsMoveUp() const { return bIsMoveUp; }
	inline bool GetbIsMoveDown() const { return bIsMoveDown; }
	inline bool GetbIsMoveLeft() const { return bIsMoveLeft; }
	inline bool GetbIsMoveRight() const { return bIsMoveRight; }
};