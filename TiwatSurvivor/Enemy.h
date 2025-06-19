#pragma once
#include "Character.h"

class APimon;
class UBullet;

class AEnemy : public ACharacter
{
public:
	AEnemy(const FAtlasSet& InAtlasSet);
	~AEnemy();

private:
	std::shared_ptr<ACharacter> TargetCharacter;

public:
	bool bIsDead = false;

private:
	virtual void OnDamage() override;

public:
	virtual void Move() override;

	bool CheckBulletCollision(const UBullet& InBullet);
	bool CheckPlayerCollision(std::shared_ptr<APimon> InPlayer);
	
	inline std::shared_ptr<ACharacter> GetTargetCharacter() { return TargetCharacter; }
	inline void SetTargetCharacter(std::shared_ptr<ACharacter> InTargetCharacter) { TargetCharacter = InTargetCharacter; }
};