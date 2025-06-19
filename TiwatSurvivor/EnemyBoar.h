#pragma once
#include "Enemy.h"


class AEnemyBoar : public AEnemy
{
public:
	AEnemyBoar(const FAtlasSet& InAtlasSet);
	~AEnemyBoar();

public:
	virtual POINT CalculateShadowPosition() override { return { Position.x + 35, Position.y + 45 }; }
};