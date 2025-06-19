#pragma once
#include <memory>

class UAtlas;

struct FAtlasSet
{
	std::shared_ptr<UAtlas> LeftAtlas;
	std::shared_ptr<UAtlas> RightAtlas;
	std::shared_ptr<UAtlas> ShadowAtlas;
};

struct FButtonImageSet
{
	std::shared_ptr<IMAGE> IdleImage = std::make_shared<IMAGE>();
	std::shared_ptr<IMAGE> HoveredImage = std::make_shared<IMAGE>();
	std::shared_ptr<IMAGE> PushedImage = std::make_shared<IMAGE>();
};