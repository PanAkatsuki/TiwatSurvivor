#pragma once
#include <graphics.h>
#include <memory>

#pragma comment(lib, "MSIMG32.LIB")

class UAtlas;
class ACharacter;

class UAnimation
{
public:
	UAnimation(std::shared_ptr<UAtlas> InAtlas, int InInterval);
	~UAnimation();

private:
	ACharacter* Owner = nullptr;

private:
	std::shared_ptr<UAtlas> Atlas;
	int Interval = 0;

	int Timer = 0;
	int FrameIndex = 0;
	bool bIsFrozen = false;

private:
	void PutImageAlpha(int InX, int InY, IMAGE* InImage) const;

public:
	void Rend(POINT InPosition, int InDeltaTime);
	void RendFrozenState(POINT InPosition, int InDeltaTime);

public:
	inline void SetOwner(ACharacter* InOwner) { Owner = InOwner; }
	inline ACharacter* GetOwner() const { return Owner; }

	inline std::shared_ptr<UAtlas> GetAtlas() const { return Atlas; }
};