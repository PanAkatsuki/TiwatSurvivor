#pragma once
#include <graphics.h>
#include <vector>
#include <memory>

class UAnimation;

class UAtlas
{
public:
	UAtlas(LPCTSTR InPath, int InNum);
	~UAtlas();

private:
	std::vector<std::shared_ptr<IMAGE>> FrameList;

public:
	inline const std::vector<std::shared_ptr<IMAGE>>& GetFrameList() const { return FrameList; }
};