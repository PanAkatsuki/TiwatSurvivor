#pragma once

#include <graphics.h>

#include <vector>
#include <memory>

class Atlas
{
public:
	std::vector<IMAGE*> m_FrameList;
public:
	Atlas(LPCTSTR path, int num);
	~Atlas();
};