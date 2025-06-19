#include "Character.h"

#include "Animation.h"
#include "Atlas.h"


ACharacter::ACharacter(const FAtlasSet& InAtlasSet)
{
	LeftAnimation = CreateAnimation(InAtlasSet.LeftAtlas, 50);
	RightAnimation = CreateAnimation(InAtlasSet.RightAtlas, 50);
	ShadowAnimation = CreateAnimation(InAtlasSet.ShadowAtlas, 100);

	CurrentAnimation = LeftAnimation;
	CurrentShadowAnimation = ShadowAnimation;
	InitializeFrameDataFromCurrentAnimation(CurrentAnimation, CurrentShadowAnimation);

	OnDamageDelegate.AddListener(std::bind(&ACharacter::OnDamage, this));
}

ACharacter::~ACharacter()
{
}

std::shared_ptr<UAnimation> ACharacter::CreateAnimation(std::shared_ptr<UAtlas> InAtlas, int InInterval)
{
	std::shared_ptr<UAnimation> NewAnimation = std::make_shared<UAnimation>(
		InAtlas,
		InInterval
	);
	NewAnimation->SetOwner(this);

	return NewAnimation;
}

void ACharacter::InitializeFrameDataFromCurrentAnimation(std::shared_ptr<UAnimation> InCurrentAnimation, std::shared_ptr<UAnimation> InCurrentShadowAnimation)
{
	if (CurrentAnimation)
	{
		FrameData.FrameLength = CurrentAnimation->GetAtlas()->GetFrameList().at(0)->getwidth();
		FrameData.FrameHeight = CurrentAnimation->GetAtlas()->GetFrameList().at(0)->getheight();
	}

	if (CurrentShadowAnimation)
	{
		FrameData.ShadowLength = CurrentShadowAnimation->GetAtlas()->GetFrameList().at(0)->getwidth();
		FrameData.ShadowHeight = CurrentShadowAnimation->GetAtlas()->GetFrameList().at(0)->getheight();
	}
}
