#pragma once
#pragma comment(lib, "MSIMG32.LIB")

#include <graphics.h>

#include <vector>

#include "Atlas.h"

class Animation
{
private:
	// Default
	int interval_ms;
	int timer;
	int idxFrame;
	Atlas* m_Atlas;
public:
	// Constructor
	Animation(Atlas* atlas, int interval);
	~Animation();

	// Rend
	void PutImageAlpha(int x, int y, IMAGE* img) const;
	void Rend(int x, int y, int delta);
};
