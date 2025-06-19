#pragma once
#include "Controller.h"

class ACharacter;

class APlayerController : public AController
{
public:
	APlayerController();
	~APlayerController();

private:
	ACharacter* Owner = nullptr;

public:
	void ProcessEvent(const ExMessage& Message);
	
public:
	inline void SetOwner(ACharacter* InOwner) { Owner = InOwner; }
	inline ACharacter* GetOwner() const { return Owner; }
};