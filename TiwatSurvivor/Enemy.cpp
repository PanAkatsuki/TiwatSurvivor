#include "Enemy.h"

#include "Pimon.h"
#include "Bullet.h"


AEnemy::AEnemy(const FAtlasSet& InAtlasSet)
	: ACharacter(InAtlasSet)
{
}

AEnemy::~AEnemy()
{
}

void AEnemy::OnDamage()
{
	mciSendString(_T("play hit from 0"), NULL, 0, NULL);
	bIsDead = true;
}

void AEnemy::Move()
{
	if (!TargetCharacter)
	{
		return;
	}

	int DirectionX = TargetCharacter->GetPosition().x - Position.x;
	int DirectionY = TargetCharacter->GetPosition().y - Position.y;

	if (DirectionX > 0)
	{
		CurrentAnimation = RightAnimation;
	}
	else if (DirectionX < 0)
	{
		CurrentAnimation = LeftAnimation;
	}

	double Length = sqrt(DirectionX * DirectionX + DirectionY * DirectionY);

	if (!Length)
	{
		return;
	}

	double NormalizedX = DirectionX / Length;
	double NormalizedY = DirectionY / Length;

	Position.x += (int)(NormalizedX * Speed);
	Position.y += (int)(NormalizedY * Speed);
}

bool AEnemy::CheckBulletCollision(const UBullet& InBullet)
{
	bool bIsOverlapX = InBullet.GetPosition().x >= Position.x && InBullet.GetPosition().x <= Position.x + FrameData.FrameLength;
	bool bIsOverlapY = InBullet.GetPosition().y >= Position.y && InBullet.GetPosition().y <= Position.y + FrameData.FrameHeight;
	
	if (bIsOverlapX && bIsOverlapY)
	{
		OnDamageDelegate.Broadcast();
		return true;
	}

	return false;
}

bool AEnemy::CheckPlayerCollision(std::shared_ptr<APimon> InPlayer)
{
	POINT CollisionPoint = { Position.x + FrameData.FrameLength / 2, Position.y + FrameData.FrameHeight / 2 };
	bool bIsOverlapX = CollisionPoint.x >= InPlayer->GetPosition().x && CollisionPoint.x <= InPlayer->GetPosition().x + InPlayer->GetFrameDate().FrameLength;
	bool bIsOverlapY = CollisionPoint.y >= InPlayer->GetPosition().y && CollisionPoint.y <= InPlayer->GetPosition().y + InPlayer->GetFrameDate().FrameHeight;
	
	if (bIsOverlapX && bIsOverlapY)
	{
		InPlayer->OnDamageDelegate.Broadcast();
		return true;
	}

	return false;
}
