#include "Animation.h"

#include "Atlas.h"
#include "TiwatSurvivorFunctionLibrary.h"


UAnimation::UAnimation(std::shared_ptr<UAtlas> InAtlas, int InInterval)
	: Atlas(InAtlas), Interval(InInterval)
{
}

UAnimation::~UAnimation()
{
}

void UAnimation::PutImageAlpha(int InX, int InY, IMAGE* InImage) const
{
	int Width = InImage->getwidth();
	int Height = InImage->getheight();
	AlphaBlend(
		GetImageHDC(NULL),
		InX, 
		InY, 
		Width,
		Height,
		GetImageHDC(InImage),
		0, 
		0, 
		Width,
		Height,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
	);
}

void UAnimation::Rend(POINT InPosition, int InDeltaTime)
{
	if (!Atlas->GetFrameList().size())
	{
		return;
	}

	IMAGE* RendImage = nullptr;

	if (bIsFrozen)
	{
		// Todo: FrozenState
	}
	else
	{
		Timer += InDeltaTime;
		if (Timer >= Interval)
		{
			FrameIndex = (FrameIndex + 1) % Atlas->GetFrameList().size();
			Timer = 0;
		}

		RendImage = Atlas->GetFrameList().at(FrameIndex).get();
	}
	
	PutImageAlpha(InPosition.x, InPosition.y, RendImage);
}

void UAnimation::RendFrozenState(POINT InPosition, int InDeltaTime)
{
	// Todo: Complete FrozenState
	static int FrozenTimer = 0;
	static const int ScanLineThickness = 5;
	static int ScanLinePositionY = 0;

	FrozenTimer += InDeltaTime;
	if (InDeltaTime)
	{

	}
}
