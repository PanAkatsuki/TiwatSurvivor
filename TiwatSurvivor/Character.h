#pragma once
#include <graphics.h>
#include <memory>

#include "EnumType.h"
#include "StructType.h"
#include "Global.h"
#include "Delegate.h"


class UAnimation;
class UAtlas;
struct FAtlasSet;

struct FCharacterFrameData
{
	int FrameLength = 0;
	int FrameHeight = 0;
	int ShadowLength = 0;
	int ShadowHeight = 0;
};

class ACharacter
{
public:
	ACharacter(const FAtlasSet& InAtlasSet);
	~ACharacter();

protected:
	unsigned int Speed = 0;
	POINT Position = { 0, 0 };

	EDirection Direction = EDirection::left;

	std::shared_ptr<UAnimation> LeftAnimation;
	std::shared_ptr<UAnimation> RightAnimation;
	std::shared_ptr<UAnimation> ShadowAnimation;

	std::shared_ptr<UAnimation> CurrentAnimation;
	std::shared_ptr<UAnimation> CurrentShadowAnimation;

	FCharacterFrameData FrameData;
	
public:
	FDelegate<> OnDamageDelegate;

protected:
	std::shared_ptr<UAnimation> CreateAnimation(std::shared_ptr<UAtlas> InAtlas, int InInterval);
	void InitializeFrameDataFromCurrentAnimation(std::shared_ptr<UAnimation> InCurrentAnimation, std::shared_ptr<UAnimation> InCurrentShadowAnimation);

	virtual void OnDamage() = 0;

public:
	virtual void Move() = 0;

public:
	inline POINT GetPosition() const { return Position; }

	inline EDirection GetDirection() const { return Direction; }
	inline void SetDirection(EDirection InDirection) { Direction = InDirection; }

	virtual POINT CalculateShadowPosition() = 0;

	inline std::shared_ptr<UAnimation> GetCurrentAnimation() { return CurrentAnimation; }

	inline std::shared_ptr<UAnimation> GetCurrentShadowAnimation() { return CurrentShadowAnimation; }

	inline const FCharacterFrameData& GetFrameDate() { return FrameData; }
};