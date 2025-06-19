#pragma once
#include <graphics.h>
#include <vector>
#include <memory>

class AEnemy;
struct FAtlasSet;

namespace UTiwatSurvivorFunctionLibrary
{
	void TryGenerateEnemyBoar(std::vector<std::shared_ptr<AEnemy>>& InEnemyList, const FAtlasSet& InAtlasSet, const int InInterval = 100);

	void DrawPlayScore(int InScore);

	std::shared_ptr<IMAGE> FlipImage(std::shared_ptr<IMAGE> InImage);
	std::shared_ptr<IMAGE> SketchImage(std::shared_ptr<IMAGE> InImage);
	std::shared_ptr<IMAGE> BlendImage(std::shared_ptr<IMAGE> InOriginalImage, std::shared_ptr<IMAGE> InBlendImage, float InRadio = 0.25f);
}