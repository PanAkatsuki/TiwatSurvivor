#pragma once
#include <graphics.h>

#include "Global.h"
#include "EnumType.h"
#include "StructType.h"

struct FButtonFrameData
{
	int Width = 0;
	int Height = 0;
};

class UButton
{
public:
	UButton(std::shared_ptr<FButtonImageSet> InButtonImageSet);
	~UButton();

protected:
	RECT Region = { 0, 0 };
	std::shared_ptr<FButtonImageSet> ButtonImageSet;
	EButtonStatus Status = EButtonStatus::Idle;
	FButtonFrameData ButtonFrameData;

private:
	bool CheckCursorHit(int x, int y);

protected:
	virtual void OnClick() = 0;

public:
	void ProcessEvent(const ExMessage& Message);

	void Rend();
};


class UStartButton : public UButton
{
public:
	UStartButton(std::shared_ptr<FButtonImageSet> InButtonImageSet);
	~UStartButton();

protected:
	virtual void OnClick() override;
};


class UQuitButton : public UButton
{
public:
	UQuitButton(std::shared_ptr<FButtonImageSet> InButtonImageSet);
	~UQuitButton();

protected:
	virtual void OnClick() override;
};